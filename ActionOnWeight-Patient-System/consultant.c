#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 256
#define SHIFT 5  /* Caesar shift */

typedef struct {
  char first[MAX];
  char last[MAX];
  char dob[9];
  char notes[1024];
} Patient;

/* --- helpers (duplicated to stay single-file) --- */
static void trim(char *s){ size_t n=strlen(s); while(n&& (s[n-1]=='\n'||s[n-1]=='\r')) s[--n]='\0'; }
static void lower(char *s){ for(;*s;++s)*s=(char)tolower((unsigned char)*s); }
static void caesar_encrypt(char *s,int k){
  for(;*s;++s){ unsigned char c=(unsigned char)*s;
    if(isprint(c)){ int base=32, span=95; *s=(char)(base+((c-base+k)%span)); }
  }
}
static void caesar_decrypt(char *s,int k){ caesar_encrypt(s,95-(k%95)); }
static void make_fname(char *out,size_t n,const char *last,const char *dob){
  snprintf(out,n,"%s%s_record.aow",last,dob);
}
static int check_login(const char *user,const char *pass_enc){
  /* demo creds (encrypted with SHIFT=5): user: "consultant", pass: "consultpass" */
  const char *U="consultant", *P="htsxzqfy%xx"; /* change to your own */
  return strcmp(user,U)==0 && strcmp(pass_enc,P)==0;
}

/* --- parse/save --- */
static int read_patient(const char *fname, Patient *p){
  FILE *fp=fopen(fname,"r"); if(!fp){ perror("fopen"); return 0; }
  char enc[4096]={0}; size_t n=fread(enc,1,sizeof(enc)-1,fp); fclose(fp); enc[n]='\0';
  caesar_decrypt(enc,SHIFT);
  char *line=strtok(enc,"\n");
  while(line){
    if(!strncmp(line,"FIRST:",6)) strncpy(p->first,line+6,sizeof(p->first)-1);
    else if(!strncmp(line,"LAST:",5)) strncpy(p->last,line+5,sizeof(p->last)-1);
    else if(!strncmp(line,"DOB:",4)) strncpy(p->dob,line+4,sizeof(p->dob)-1);
    else if(!strncmp(line,"NOTES:",6)) strncpy(p->notes,line+6,sizeof(p->notes)-1);
    line=strtok(NULL,"\n");
  }
  return 1;
}
static int write_patient(const char *fname,const Patient *p){
  char buf[4096];
  snprintf(buf,sizeof(buf),"FIRST:%s\nLAST:%s\nDOB:%s\nNOTES:%s\n",
           p->first,p->last,p->dob,p->notes);
  caesar_encrypt(buf,SHIFT);
  FILE *fp=fopen(fname,"w"); if(!fp){ perror("fopen"); return 0; }
  fputs(buf,fp); fclose(fp); return 1;
}

int main(void){
  char user[MAX], pass[MAX], pass_enc[MAX];
  printf("== Consultant Login ==\nUser: "); fgets(user,MAX,stdin); trim(user);
  printf("Pass: "); fgets(pass,MAX,stdin); trim(pass);
  strncpy(pass_enc,pass,MAX-1); pass_enc[MAX-1]='\0'; caesar_encrypt(pass_enc,SHIFT);
  if(!check_login(user,pass_enc)){ puts("Invalid credentials."); return 1; }

  char last[MAX], dob[9], fname[512];
  puts("\n== Open Patient Record ==");
  printf("Last name: "); fgets(last,MAX,stdin); trim(last); lower(last);
  do { printf("DOB (DDMMYYYY): "); fgets(dob,sizeof(dob),stdin); trim(dob); } while(strlen(dob)!=8);
  make_fname(fname,sizeof(fname),last,dob);

  Patient p={0};
  if(!read_patient(fname,&p)){ printf("No record: %s\n", fname); return 1; }

  printf("\n-- Current Record --\nFirst: %s\nLast: %s\nDOB: %s\nNotes: %s\n",
         p.first,p.last,p.dob,p.notes);

  char extra[1024];
  printf("\nAdd consultant notes (blank to skip): ");
  fgets(extra,sizeof(extra),stdin); trim(extra);
  if(extra[0]){
    strncat(p.notes," | ",sizeof(p.notes)-strlen(p.notes)-1);
    strncat(p.notes,extra,sizeof(p.notes)-strlen(p.notes)-1);
    if(!write_patient(fname,&p)){ puts("Save failed."); return 1; }
    puts("Updated and re-encrypted.");
  } else {
    puts("No changes saved.");
  }
  return 0;
}
