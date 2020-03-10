//
// Created by stas on 10.03.2020.
//

#include "TwoDimensionalDTree.h"

TwoDimensionalDTree::Node *TwoDimensionalDTree::insert(int *point) {
    this->root = insertRec(root, point, 0);
    return this->root;
}

TwoDimensionalDTree::Node *TwoDimensionalDTree::insertRec(TwoDimensionalDTree::Node *root, int *point, unsigned depth) {
    if (root == nullptr)
        return new Node(point[0], point[1]);

    // Calculate current dimension
    unsigned cd = depth % 2;

    // Compare the new point with root on current dimension 'cd'
    // and decide the left or right subtree
    if (point[cd] < (root->point[cd]))
        root->left = insertRec(root->left, point, depth + 1);
    else
        root->right = insertRec(root->right, point, depth + 1);

    return root;
}

bool TwoDimensionalDTree::search(TwoDimensionalDTree::Node *root, int *point) {
    // Pass current depth as 0
    return searchRec(root, point, 0);
}

bool TwoDimensionalDTree::searchRec(TwoDimensionalDTree::Node *root, int *point, unsigned depth) {
    // Base cases
    if (root == nullptr)
        return false;
    if ((root->point[0] == point[0] and root->point[1] == point[1]))
        return true;

    // Current dimension
    unsigned cd = depth % 2;

    // Compare point with root with respect to cd (Current dimension)
    if (point[cd] < root->point[cd])
        return searchRec(root->left, point, depth + 1);

    return searchRec(root->right, point, depth + 1);
}

std::vector<std::pair<int,int>> TwoDimensionalDTree::findPointsInArea(int leftX, int leftY, int rightX, int rightY) {
    findPointsInAreaRecY(leftX, leftY, rightX, rightY, root);
    return points_in_area;
}

void TwoDimensionalDTree::findPointsInAreaRecY(int leftX, int leftY, int rightX, int rightY,
                                               TwoDimensionalDTree::Node *curNode) {

    bool goneLeft = false, goneRight = false;
    if (leftX < curNode->point[0]) {
        if (curNode->left != nullptr) findPointsInAreaRecX(leftX, leftY, rightX, rightY, curNode->left);
        goneLeft = true;
    }
    if (curNode->point[0] < rightX) {
        if (curNode->right != nullptr) findPointsInAreaRecX(leftX, leftY, rightX, rightY, curNode->right);
        goneRight = true;
    }
    if (goneLeft && goneRight && rightY < curNode->point[1] && leftY > curNode->point[1]) {
        points_in_area.push_back(std::make_pair(curNode->point[0],curNode->point[1]));
    }
}

void TwoDimensionalDTree::findPointsInAreaRecX(int leftX, int leftY, int rightX, int rightY,
                                               TwoDimensionalDTree::Node *curNode) {
    bool goneLeft = false, goneRight = false;
    if (rightY < curNode->point[1]) {
        if (curNode->left != nullptr) findPointsInAreaRecY(leftX, leftY, rightX, rightY, curNode->left);
        goneLeft = true;
    }
    if (curNode->point[1] < leftY) {
        if (curNode->right != nullptr) findPointsInAreaRecY(leftX, leftY, rightX, rightY, curNode->right);
        goneRight = true;
    }
    if (goneLeft && goneRight && leftX < curNode->point[0] && rightX > curNode->point[0]) {
        points_in_area.push_back(std::make_pair(curNode->point[0],curNode->point[1]));
    }
}

TwoDimensionalDTree::TwoDimensionalDTree() : root(nullptr) {

}
