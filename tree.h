#pragma once

#include<stdio.h>
#include<stdlib.h>
typedef int KeyType;
typedef char InfoType;

typedef struct
{
    KeyType key;
    InfoType otherinfo;
    int height; // ƽ������
} ElemType;

typedef struct BiNode
{
    ElemType data;
    struct BiNode* lchild, * rchild;
} BiNode, * BiTree;

//�������
void InOrderTraverse(BiTree T);
//�ͷ����Ŀռ�
void FreeTree(BiTree root);
BiTree DeleteNode(BiTree T, KeyType key);
BiTree Insert(BiTree T, KeyType arr, InfoType ch);
BiTree Balance(BiTree T);
BiTree RotateRL(BiTree A);
BiTree RotateLR(BiTree A);
BiTree RotateRR(BiTree A);
BiTree RotateLL(BiTree A);
int Height(BiTree T);
