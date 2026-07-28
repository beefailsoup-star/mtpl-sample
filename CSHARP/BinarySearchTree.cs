using System;
using System.Collections.Generic;

namespace MtplSample
{
    public class BinarySearchTree<T> where T : IComparable<T>
    {
        private TreeNode<T> _root;

        public int Count { get; private set; }

        public void Insert(T value)
        {
            _root = InsertNode(_root, value);
            Count++;
        }

        private TreeNode<T> InsertNode(TreeNode<T> node, T value)
        {
            if (node == null) return new TreeNode<T>(value);

            if (value.CompareTo(node.Value) < 0)
                node.Left = InsertNode(node.Left, value);
            else if (value.CompareTo(node.Value) > 0)
                node.Right = InsertNode(node.Right, value);
            else
                Count--;
            return node;
        }

        public bool Search(T value)
        {
            return SearchNode(_root, value) != null;
        }

        private TreeNode<T> SearchNode(TreeNode<T> node, T value)
        {
            if (node == null) return null;
            if (value.CompareTo(node.Value) == 0) return node;
            if (value.CompareTo(node.Value) < 0)
                return SearchNode(node.Left, value);
            return SearchNode(node.Right, value);
        }

        public void Delete(T value)
        {
            _root = DeleteNode(_root, value);
        }

        private TreeNode<T> DeleteNode(TreeNode<T> node, T value)
        {
            if (node == null) return null;

            if (value.CompareTo(node.Value) < 0)
                node.Left = DeleteNode(node.Left, value);
            else if (value.CompareTo(node.Value) > 0)
                node.Right = DeleteNode(node.Right, value);
            else
            {
                if (node.Left == null) return node.Right;
                if (node.Right == null) return node.Left;

                var minNode = FindMin(node.Right);
                node.Value = minNode.Value;
                node.Right = DeleteNode(node.Right, minNode.Value);
            }
            return node;
        }

        private TreeNode<T> FindMin(TreeNode<T> node)
        {
            while (node.Left != null) node = node.Left;
            return node;
        }

        public List<T> InOrderTraversal()
        {
            var result = new List<T>();
            InOrder(_root, result);
            return result;
        }

        private void InOrder(TreeNode<T> node, List<T> result)
        {
            if (node == null) return;
            InOrder(node.Left, result);
            result.Add(node.Value);
            InOrder(node.Right, result);
        }
    }

    public class TreeNode<T>
    {
        public T Value { get; set; }
        public TreeNode<T> Left { get; set; }
        public TreeNode<T> Right { get; set; }

        public TreeNode(T value)
        {
            Value = value;
        }
    }
}
