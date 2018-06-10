/*#include <iostream>
#include <cmath>
int CalSiPMID(float x, float y);*/

void gamma_process(int FileID, int FileIDend)
{
    srand((unsigned)time(NULL));  
	gROOT->Reset();
	char outputfile[255];
	sprintf(outputfile, "test_%d", FileID);
	FILE* fp=fopen(outputfile, "wb");
	//int EventID = 0;

	for(int j=FileID; j<=FileIDend; j++)
	{
		char rootfilename[255];
		sprintf(rootfilename, "./ANNGate/gate.root"", j);
		TFile file(rootfilename);
		
		/*char outputfile[255];
		sprintf(outputfile, "test_%d", j);
		FILE* fp=fopen(outputfile, "wb");*/
		
		if(file.IsZombie())
		{ 
			cout<<j<<endl;
			continue;
		}
		TTree* singlestree = (TTree*)gDirectory->Get("Hits");
		double time;
		int sourceID;
		float posX,posY,posZ;
		float edep;
		char processName[255];
		double time_tmp = 0;
		double detarray[36];
		double time_array[2000];
		double sipmid_array[2000];
		int index_scin = 0;
		for(int sipmid = 0; sipmid < 6 * 6; sipmid++)
		{
			detarray[sipmid] = 0;
		}
		for(int i = 0; i < 2000; i++)
		{
			time_array[i] = 0;
			sipmid_array[i] = 0;
		}
		singlestree->SetBranchAddress("time", &time);
		singlestree->SetBranchAddress("posZ", &posZ);
		singlestree->SetBranchAddress("posX", &posX);
		singlestree->SetBranchAddress("posY", &posY);
		singlestree->SetBranchAddress("edep", &edep);
		singlestree->SetBranchAddress("processName", &processName);
		singlestree->SetBranchAddress("sourceID", &sourceID);
		int nsingles  = singlestree->GetEntries();
		double posX_, posY_, posZ_, a, sourceID_;
		for (int i = 0; i < nsingles; i++)
		{
			singlestree->GetEntry(i); 
			if(fabs(time-time_tmp)>=1e-6)
			{
				if(time_tmp!=0)
				{
					//EventID = EventID + 1;
					fwrite(&a, sizeof(a), 1, fp);
					fwrite(&posX_, sizeof(posX_), 1, fp);
					fwrite(&posY_, sizeof(posY_), 1, fp);
					fwrite(&posZ_, sizeof(posZ_), 1, fp);
					fwrite(detarray, sizeof(double), sizeof(detarray)/sizeof(double), fp);
					fwrite(&sourceID_, sizeof(sourceID_), 1, fp);
					for(int sipmid = 0; sipmid < 6 * 6; sipmid++)
					{
						detarray[sipmid] = 0;
					}
					//if(EventID>=1000)
					//	break;
					index_scin = 0;
					for(int i = 0; i < index_scin; i++)
					{
						time_array[i] = 0;
						sipmid_array[i] = 0;
					}
				}
				
				cout<<" "<<j<<" "<<time_tmp<<" "<<time<<" "<<fabs(time-time_tmp)<<" "<<processName<<" "<<posZ<<endl;
				//double a;
				if(strcmp(processName,"PhotoElectric")==0)
					a = 0;
				else if(strcmp(processName,"Compton")==0)
					a=-1;
				else
					a=-2;
				//fwrite(&a, sizeof(a), 1, fp);
				
				posX_ = (double)posX;
				posY_ = (double)posY;
				posZ_ = (double)posZ;
				sourceID_ = (double)sourceID;
				//cout<<posX_<<" "<<posY_<<" "<<sourceID_<<endl;
				//fwrite(&posX_, sizeof(posX_), 1, fp);
				//fwrite(&posY_, sizeof(posY_), 1, fp);
				//fwrite(&posZ_, sizeof(posZ_), 1, fp);
				
				time_tmp = time;
			}
			else
			{
				if(strcmp(processName,"Transportation")==0)// && pe_flag == 1)
				{
					//double ran = (double)rand();
					//cout<<RAND_MAX<<endl;
					//(ran/RAND_MAX<=QE)
					//{
						int SiPMID = CalSiPMID(posX, posY);
						if(SiPMID!=-1)
						{
							detarray[SiPMID] = detarray[SiPMID] + 1;
							time_array[index_scin] = time;
							sipmid_array[index_scin] = SiPMID;
							index_scin++;
						}
					//}
				}
				//time_tmp = time;
			}
		}
		file.Close();
		//fclose(fp);
	}
	fclose(fp);
}
	  


int CalSiPMID(float x, float y)
{
	int SiPMxNum = 6;
	int SiPMyNum = 6;
	float SiPMasize = 3;
	float SiPMtsize = 4.1667;
	float x_start = -SiPMtsize*SiPMxNum/2;
	float y_start = -SiPMtsize*SiPMyNum/2;
	float a = (x - x_start)/SiPMtsize - floor((x - x_start)/SiPMtsize);
	float b = (y - y_start)/SiPMtsize - floor((y - y_start)/SiPMtsize);
	float left = (SiPMtsize - SiPMasize)/2/SiPMtsize;
	float right = (SiPMtsize + SiPMasize)/2/SiPMtsize;
	//cout<<left<<" "<<right<<" "<<endl;
	if(a>=left && a<=right && b>=left && b<=right)
	{
		int SiPMIDx = floor((x - x_start)/SiPMtsize);
		int SiPMIDy = floor((y - y_start)/SiPMtsize);
		return SiPMxNum * SiPMIDy + SiPMIDx;
	}
	else
	{
		return -1;
	}
}
