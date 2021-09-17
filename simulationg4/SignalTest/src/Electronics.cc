#include "Electronics.hh"

Electronics::Electronics()
{}



Electronics::~Electronics()
{}



int Electronics::ProcessPulse(std::vector<double> &currentIn,std::vector<double> &current_time_In, std::vector<double> &pulseOut,std::vector<double>&pulse_time_Out)
{
  //current_time_in is in ns
  // Electronics in microseco
  std::cout<< "[Electronics] I am here "<<std::endl;
  double t0 = current_time_In[0]/1.e3;
  double dt = (current_time_In[current_time_In.size()-1] - current_time_In[0])/1.e3;
  if(dt<10*m_tRC)
    dt=10.*m_tRC;
  unsigned int nbins = (int)(dt / m_tSample);

  double im_tRC=1./m_tRC;
  for(unsigned int i=0; i<nbins; ++i)
    {
      pulse_time_Out.push_back(t0+i* m_tSample);
      pulseOut.push_back(0.);
    }

  unsigned int currentInSize=currentIn.size();
  unsigned int pulseOutSize=pulseOut.size();
  for(unsigned int i=0; i<currentInSize; ++i)
    {
      //if(fabs(currentIn[i])<1e-9)
      //continue;
      double currentInTmp=currentIn[i];
      if(fabs(currentInTmp)<0.)
	std::cout << "[Electronics] input "<< i << " " <<currentInTmp<<std::endl;
      double current_time = current_time_In[i]*1.e-3;
      double pulseSize = currentInTmp*m_fCtomV;

      for(unsigned int j=0; j<pulseOutSize; ++j)
	{
	  double pulse_time_OutTmp=pulse_time_Out[j];
	  if(current_time>pulse_time_OutTmp)
	    continue;
	  pulseOut[j] += pulseSize * exp((-pulse_time_OutTmp+current_time)*im_tRC);
	  //std::cout << j << " "<<pulseOut[j]<<std::endl;
	}
    }
  return 0;
}
