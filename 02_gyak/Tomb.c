FILE *fp;
fp=fopen("output.txt","w+");
for(int i=0;i<15;i++)
{a[i]=i;
fprintf(fp,"%f\n",a[i]);
}
fclose(fp);