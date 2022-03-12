#pragma warning(disable: 4996)

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

int main(int argc, char *argv[]) //��ɾ� ���ڷ� �׽�Ʈ ���� �̸��� main �Լ��� ����
{
    // �ʿ��� ���� ����
    FILE *fp;
    node *head = NULL;
    int id;
    char name[10];
    node *result;
    int cmd;
    // ���� ����
    fp = fopen(argv[1], "rt"); //���ڷ� �Ѿ�� �����̸��� �̿��Ͽ� ���� ����
    if (fp == NULL)
    {
        printf("������ ���� ���� ���� \n");
        exit(-1);
    }
    // ��ɾ �о� �ʿ��� �Լ� ȣ��
    while (1)
    {
        fscanf(fp, "%d", &cmd);
        printf("��� : %d \n", cmd);
        switch (cmd)
        {
        case 1:
            fscanf(fp, "%d %s", &id, name);
            addNode(&head, id, name); //��尡 �־�� ù��° ��� ���鶧 ���� ����
            break;
        case 2:
            fscanf(fp, "%d", &id);
            result = searchNode(head, id);
            printf("�˻� ��� : %s \n", result->name);
            break;
        case 3:
            fscanf(fp, "%d", &id);
            result = deleteNode(&head, id);
            free(result);
            break;
        case 4:
            printf("��ü ��� ��� \n");
            printNode(head);
            break;
        case 5:
            freeAllNode(head);
            break;
        case 6: // ���α׷� ����
        default:
            break;
        }
        if (cmd == 6)
            break;
    }
    // ���� �ݱ�
    fclose(fp);
    return 0;
}