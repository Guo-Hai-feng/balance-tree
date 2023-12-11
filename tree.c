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

    // �������߶ȴ���������
    if (balance > 1)
    {
        // ���������������߶ȴ��ڵ�����������������
        if (Height(T->lchild->lchild) >= Height(T->lchild->rchild))
        {
            return RotateLL(T);
        }
        // ���������������߶�С����������������
        else
        {
            return RotateLR(T);
        }
    }
    // �������߶ȴ���������
    else if (balance < -1)
    {
        // ���������������߶ȴ��ڵ�����������������
        if (Height(T->rchild->rchild) >= Height(T->rchild->lchild))
        {
            return RotateRR(T);
        }
        // ���������������߶�С����������������
        else
        {
            return RotateRL(T);
        }
    }

    return T; // ���Ѿ�ƽ��
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

    // ���½ڵ�ĸ߶�
    T->data.height = max(Height(T->lchild), Height(T->rchild)) + 1;

    // ƽ����
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
        // �ҵ�Ҫɾ���Ľڵ�

        // ���һ�����ӽڵ��ֻ��һ���ӽڵ�
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

        // ��������������ӽڵ�
        BiTree temp = FindMin(T->rchild); // �ҵ�����������С�ڵ�

        // ������������С�ڵ��ֵ���Ƹ���ǰ�ڵ�
        T->data = temp->data;

        // ɾ������������С�ڵ�
        T->rchild = DeleteNode(T->rchild, temp->data.key);
    }

    // ���½ڵ�ĸ߶�
    T->data.height = max(Height(T->lchild), Height(T->rchild)) + 1;

    // ƽ����
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

    // ɾ���ڵ� 45
    KeyType keyToDelete = 45;
    T = DeleteNode(T, keyToDelete);

    printf("\nAVL Tree after deleting node with key %d:\n", keyToDelete);
    InOrderTraverse(T);

    FreeTree(T);
    return 0;
}
