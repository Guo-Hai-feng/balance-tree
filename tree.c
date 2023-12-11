#include"tree.h"
int Height(BiTree T)
{
    if (T == NULL)
    {
        return 0;
    }
    return T->data.height;
}


BiTree RotateLL(BiTree A)
{
    BiTree B = A->lchild;
    A->lchild = B->rchild;
    B->rchild = A;
    A->data.height = max(Height(A->lchild), Height(A->rchild)) + 1;
    B->data.height = max(Height(B->lchild), Height(B->rchild)) + 1;
    return B;
}

BiTree RotateRR(BiTree A)
{
    BiTree B = A->rchild;
    A->rchild = B->lchild;
    B->lchild = A;
    A->data.height = max(Height(A->lchild), Height(A->rchild)) + 1;
    B->data.height = max(Height(B->lchild), Height(B->rchild)) + 1;
    return B;
}

BiTree RotateLR(BiTree A)
{
    A->lchild = RotateRR(A->lchild);
    return RotateLL(A);
}

BiTree RotateRL(BiTree A)
{
    A->rchild = RotateLL(A->rchild);
    return RotateRR(A);
}


BiTree Balance(BiTree T)
{
    int balance = Height(T->lchild) - Height(T->rchild);

    // 左子树高度大于右子树
    if (balance > 1)
    {
        // 左子树的左子树高度大于等于左子树的右子树
        if (Height(T->lchild->lchild) >= Height(T->lchild->rchild))
        {
            return RotateLL(T);
        }
        // 左子树的左子树高度小于左子树的右子树
        else
        {
            return RotateLR(T);
        }
    }
    // 右子树高度大于左子树
    else if (balance < -1)
    {
        // 右子树的右子树高度大于等于右子树的左子树
        if (Height(T->rchild->rchild) >= Height(T->rchild->lchild))
        {
            return RotateRR(T);
        }
        // 右子树的右子树高度小于右子树的左子树
        else
        {
            return RotateRL(T);
        }
    }

    return T; // 树已经平衡
}


BiTree Insert(BiTree T, KeyType arr, InfoType ch)
{
    if (!T)
    {
        BiTree temp = (BiTree)malloc(sizeof(BiNode));
        if (temp == NULL)
        {
            return NULL;
        }
        temp->data.key = arr;
        temp->data.otherinfo = ch;
        temp->data.height = 1;
        temp->lchild = temp->rchild = NULL;
        return temp;
    }

    if (arr < T->data.key)
    {
        T->lchild = Insert(T->lchild, arr, ch);
    }
    else if (arr > T->data.key)
    {
        T->rchild = Insert(T->rchild, arr, ch);
    }

    // 更新节点的高度
    T->data.height = max(Height(T->lchild), Height(T->rchild)) + 1;

    // 平衡树
    return Balance(T);
}



BiTree DeleteNode(BiTree T, KeyType key)
{
    if (!T)
    {
        printf("Key not found\n");
        return NULL;
    }

    if (key < T->data.key)
    {
        T->lchild = DeleteNode(T->lchild, key);
    }
    else if (key > T->data.key)
    {
        T->rchild = DeleteNode(T->rchild, key);
    }
    else
    {
        // 找到要删除的节点

        // 情况一：无子节点或只有一个子节点
        if (T->lchild == NULL)
        {
            BiTree temp = T->rchild;
            free(T);
            return temp;
        }
        else if (T->rchild == NULL)
        {
            BiTree temp = T->lchild;
            free(T);
            return temp;
        }

        // 情况二：有两个子节点
        BiTree temp = FindMin(T->rchild); // 找到右子树的最小节点

        // 将右子树的最小节点的值复制给当前节点
        T->data = temp->data;

        // 删除右子树的最小节点
        T->rchild = DeleteNode(T->rchild, temp->data.key);
    }

    // 更新节点的高度
    T->data.height = max(Height(T->lchild), Height(T->rchild)) + 1;

    // 平衡树
    return Balance(T);
}

void FreeTree(BiTree root)
{
    if (root != NULL)
    {
        FreeTree(root->lchild);
        FreeTree(root->rchild);
        free(root);
    }
}

void InOrderTraverse(BiTree T)
{
    if (T != NULL)
    {
        InOrderTraverse(T->lchild);
        printf("%d ", T->data.key);
        InOrderTraverse(T->rchild);
    }
}

int main()
{
    int arr[7] = { 45, 24, 53, 45, 12, 24, 90 };
    BiTree T = NULL;

    for (int i = 0; i < 7; i++)
    {
        T = Insert(T, arr[i], 'a');
    }

    printf("Original AVL Tree:\n");
    InOrderTraverse(T);

    // 删除节点 45
    KeyType keyToDelete = 45;
    T = DeleteNode(T, keyToDelete);

    printf("\nAVL Tree after deleting node with key %d:\n", keyToDelete);
    InOrderTraverse(T);

    FreeTree(T);
    return 0;
}
