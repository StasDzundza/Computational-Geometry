//
// Created by stas on 10.03.2020.
//

#ifndef INC_2DTREE_TWODIMENSIONALDTREE_H
#define INC_2DTREE_TWODIMENSIONALDTREE_H

#include <vector>
#include <utility>

class TwoDimensionalDTree {
public:
    struct Node {
        Node(int x, int y) {
            point[0] = x;
            point[1] = y;
            left = right = nullptr;
        }

        int point[2];
        Node *left, *right;
    };

    TwoDimensionalDTree();

    Node *insert(int point[]);

    Node *insertRec(Node *root, int point[], unsigned depth);

    bool search(Node* root, int point[]);

    bool searchRec(Node* root, int point[], unsigned depth);

    std::vector<std::pair<int,int>> findPointsInArea(int leftX,int leftY,int rightX,int rightY);

    void findPointsInAreaRecY(int leftX,int leftY,int rightX,int rightY,Node*curNode);

    void findPointsInAreaRecX(int leftX,int leftY,int rightX,int rightY,Node*curNode);

private:
    Node*root;

    std::vector<std::pair<int,int>>points_in_area;
};


#endif //INC_2DTREE_TWODIMENSIONALDTREE_H
