#ifndef _FOLLOW_H_
#define _FOLLOW_H_


//
// �ڴ˴����� C ��׼��ͷ�ļ�
//


#include <stdio.h>


//
// �ڴ˴���������ͷ�ļ�
//


//
// �ڴ˴��������ݽṹ
//


#define MAX_STR_LENGTH 64

struct _Rule;
typedef struct _RuleSymbol{
	struct _RuleSymbol* pNextSymbol; // ָ����һ�� Symbol
	int isToken;					 // �Ƿ�Ϊ�ս����1 ��ʾ�ս����0 ��ʾ���ս��
	char SymbolName[MAX_STR_LENGTH]; // �ս���ͷ��ս�������ơ�	
}RuleSymbol;

typedef struct _Rule{
	char RuleName[MAX_STR_LENGTH];	 // �ķ�������
	struct _RuleSymbol* pFirstSymbol;// ָ���ķ��ĵ�һ�� Symbol
	struct _Rule* pNextRule;		 // ָ����һ���ķ�
}Rule;

typedef struct _Set{
	char Name[MAX_STR_LENGTH];		  // ���ϵ�����
	char Terminal[32][MAX_STR_LENGTH];// �ս������
	int nTerminalCount;				  // ����Ԫ�ظ���
}Set;

typedef struct _SetList{
	Set Sets[32];	// ��������
	int nSetCount;	// ����Ԫ�ظ���
}SetList;


//
// �ڴ˴���������
//

void First(const Rule* pHead, SetList* pFirstSetList);
void Follow(const Rule* pHead, SetList* pFollowSetList, SetList* pFirstSetList);
Set* GetSet(SetList* pSetList, const char* pName);
void AddOneSet(SetList* pSetList, const char* pName);
int AddTerminalToSet(Set* pSet, const char* pTerminal);
int AddSetToSet(Set* pDesSet, const Set* pSrcSet);
int SetHasVoid(const Set* pSet);

Rule* InitRules();
Rule* CreateRule(const char* pRuleName);
RuleSymbol* CreateSymbol();

void PrintRule(const Rule* pHead);


//
// �ڴ�����ȫ�ֱ���
//

extern const char* VoidSymbol;
const char* DollarSymbol;

#endif /* _FOLLOW_H_ */