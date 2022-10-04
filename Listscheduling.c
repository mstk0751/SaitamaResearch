#include <stdio.h>
int n = 11;
char DLM[] = " ";
char buf[256];
char *ptr, *ptr1, *ptr2;
char *pTokenContext;
char *out = "result.csv";
char *strFilename = "List.txt";
FILE *fp2; 
FILE *fp;
char buf[256];
int nFrom, nTo;
EDGE *pEdge;
int nUpdate, nPriority0;

typedef struct ntypeRec{
	struct ntypeRec *next; // リストで記録
	char *cNtype; // 演算種類名
	int nNtype; // 演算種類番号
	int nComp; // 演算時間
} NTYPE;

typedef struct NodeRec{
	char *cName; // 名前
	int nNtype; // 演算種類
	int nComp; // 実行時間
	int nTime; // 実行開始時刻
	int nPriority; // 優先度
	struct EdgeRec *listInEdge; // 入力枝情報
	struct EdgeRec *listOutEdge; // 出力枝情報
} NODE;

struct NodeRec node[10];

typedef struct EdgeRec{
	struct EdgeRec *next;
	int nfrom;
	int nTo;
} EDGE;

if(_tfopen_s(&fp, strFilename, _T("r")) != 0)
	return;

while(1){
	fgets(buf, 255, fp);
	if(feof(fp)) break;
	if(buf[0] == 'N') nNodeCount++;
}

node = (NODE*)malloc(nNodeCount*sizeof(NODE));
fseek(fp, 0, SEEK_SET);
while(1){
	if(strlen(buf) > 0 && buf[strlen(buf) - 1] == '\n') buf[strlen(buf) - 1] = '\0';
	NTYPE *pNtype, *listNtype = NULL;
	int nNtypeCount=0;
	switch(buf[0]){
		case 'P':
			ptr = strtok_s(buf, DLM, &pTokenContext);
			ptr1 = strtok_s(NULL, DLM, &pTokenContext);
			ptr2 = strtok_s(NULL, DLM, &pTokenContext);
			pNtype = (NTYPE *)malloc(sizeof(NTYPE));
			pNtype->cNtype = _strdup(ptr1);
			pNtype->cNtype = nNtypeCount++;
			pNtype->cNtype = atoi(ptr2);
			pNtype->next = listNtype;
			listNtype = pNtype;
			break;
		
		case 'N':
			ptr = strtok_s(buf, DLM, &pTokenContext);
			ptr1 = strtok_s(NULL, DLM, &pTokenContext);
			ptr2 = strtok_s(NULL, DLM, &pTokenContext);
			node[nIndexNode].cName = _strdup(ptr1);
			for(pNtype=listNtype; pNtype; pNtype=pNtype->next){
				if(strcmp(ptr2,pNtype->cNtype) == 0) break;
			}
			if(pNtype == NULL) continue;
			node[nIndexNode].nNtype = pNtype->nNtype;
			node[nIndexNode].nComp = pNtype->nComp;
			node[nIndexNode].listInEdge = NULL;
			node[nIndexNode].listOutEdge = NULL;
			nIndexNode++;
			break;
		
		case 'E':
			ptr = strtok_s(buf, DLM, &pTokenContext);
			ptr1 = strtok_s(NULL, DLM, &pTokenContext);
			ptr2 = strtok_s(NULL, DLM, &pTokenContext);
			for(nFrom=0 ; nFrom<nNodeCount ; nFrom++){
				if(strcmp(ptr1,node[nFrom].cName) == 0) break;
			}
			if(nFrom >= nNodeCount) continue;
			for(nTo=0; nTo<nNodeCount; nTo++){
			if(strcmp(ptr2,node[nTo].cName) == 0) break;
			}
			if( nTo >= nNodeCount ) continue;
			pEdge = (EDGE *)malloc(sizeof(EDGE));
			pEdge->nFrom = nFrom;
			pEdge->nTo = nTo;
			pEdge->next = node[nFrom].listOutEdge;
			node[nFrom].listOutEdge = pEdge;
			pEdge = (EDGE *)malloc(sizeof(EDGE));
			pEdge->nFrom = nFrom;
			pEdge->nTo = nTo;
			pEdge->next = node[nTo].listInEdge;
			node[nTo].listInEdge = pEdge;
			break;
	}
}
fclose(fp);

while(1){
	nUpdate = 0;
	for(k=0; k<nNodeCount; k++){
		nPriority0 = node[k].nPriority;
		for(pEdge=node[k].listOutEdge ; pEdge ; pEdge=pEdge->next){
			n = pEdge->nTo;
			if(nPriority0 > node[n].nPriority-node[k].nComp)
				nPriority0 = node[n].nPriority-node[k].nComp;
			}
			if(node[k].nPriority > nPriority0){
				node[k].nPriority = nPriority0;
				nUpdate = 1;
			}
		}
		if(nUpdate == 0) break;
}

int **nFUUsage = (int **)malloc(nNtypeCount*sizeof(int *));
for(k=0 ; k<nNtypeCount ; k++){
	nFUUsage[k] = (int *)malloc(nTimeMax*sizeof(int));
	for(t=0 ; t<nTimeMax ; t++) nFUUsage[k][t] = 0;
}

for(nPriority=nPriorityMin ; nPriority<0 ; nPriority++){
	for(k=0 ; k<nNodeCount ; k++){
		if(node[k].nPriority != nPriority) continue;
		// ここに来たとき、演算kは優先度nPriority演算kの実行時刻を決める;//
	}
}

for( t=t0 ; ; t++ ){
	for( t1=t ; t1<t+node[k].nComp ; t1++ ){
		if( nFUUsage[nNtype][t1]+1>nFUMax[nNtype] ) break;
	}
	if( t1>=t+node[k].nComp ) break;
}

node[k].nTime = t;
for( t1=t ; t1<t+node[k].nComp ; t1++ ) nFUUsage[nNtype][t1]++;

while(listNtype){
	pNtype = listNtype;
	listNtype = listNtype->next;
	free( pNtype->cNtype );
	free( pNtype );
}

int main(){
	fp2 = fopen(out, "w");
	if (fp2 == NULL){
		printf("%sファイルが開けません", out);
		return -1;
	}

	while(n--){
		fprintf(fp2, "%s %d\n", );
	}

	fclose(fp2);
	printf( "%s ファイル書き込みが終わりました¥n", out);
	return 0;
}