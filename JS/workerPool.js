const { Worker } = require('worker_threads');

class WorkerPool {
  constructor(workerPath, poolSize = 4, workerOptions = {}) {
    this.workerPath = workerPath;
    this.poolSize = poolSize;
    this.workerOptions = workerOptions;
    this.workers = new Set();
    this.idleWorkers = [];
    this.taskQueue = [];
    this._activeTasks = 0;
    this._initWorkers();
  }

  _initWorkers() {
    for (let i = 0; i < this.poolSize; i++) {
      this._createWorker();
    }
  }

  _createWorker() {
    const worker = new Worker(this.workerPath, this.workerOptions);
    this.workers.add(worker);
    this.idleWorkers.push(worker);

    worker.on('message', (result) => {
      this._activeTasks--;
      if (worker._currentResolve) {
        worker._currentResolve(result);
        worker._currentResolve = null;
        worker._currentReject = null;
      }
      this.idleWorkers.push(worker);
      this._processQueue();
    });

    worker.on('error', (err) => {
      this._activeTasks--;
      if (worker._currentReject) {
        worker._currentReject(err);
        worker._currentResolve = null;
        worker._currentReject = null;
      }
      this.workers.delete(worker);
      this._createWorker();
      this._processQueue();
    });

    worker.on('exit', (code) => {
      if (code !== 0 && worker._currentReject) {
        worker._currentReject(new Error(`Worker exited with code ${code}`));
        worker._currentResolve = null;
        worker._currentReject = null;
      }
      this.workers.delete(worker);
      this._createWorker();
    });

    return worker;
  }

  run(data) {
    return new Promise((resolve, reject) => {
      this.taskQueue.push({ data, resolve, reject });
      this._processQueue();
    });
  }

  _processQueue() {
    if (this.taskQueue.length === 0) return;
    if (this.idleWorkers.length === 0) return;

    const task = this.taskQueue.shift();
    const worker = this.idleWorkers.pop();
    worker._currentResolve = task.resolve;
    worker._currentReject = task.reject;
    this._activeTasks++;
    worker.postMessage(task.data);
  }

  terminate() {
    for (const worker of this.workers) {
      worker.terminate();
    }
    this.workers.clear();
    this.idleWorkers = [];
    this.taskQueue = [];
    this._activeTasks = 0;
  }
}

module.exports = { WorkerPool };
