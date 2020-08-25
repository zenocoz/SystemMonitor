#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
    float Utilization();  

 private:
    //Processor() : utilization_(Utilization()) {}
    float utilization_;
};

#endif