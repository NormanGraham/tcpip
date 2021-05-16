// xy_tcpip.h 

#ifndef xy_tcpip_h 
#define xy_tcpip_h 
   
    class xy_buffer { 
       public: 
           char *ptr = NULL; 
           unsigned short allocated = 0;
           unsigned short ip = 0;
      
           void bufferAllocate( unsigned short A ) { 
                   if ( ptr )  
                     delete [] ptr; 
                   ptr = new unsigned char[ A ];
                   ip = 0; 
                   allocated = A;
           }; 
           void bufferFree() { 
                 if ( ptr ) {
                   delete [] ptr ;
                 }
                 allocated = 0; 
                 ip = 0;
           };
           ~xy_buffer() { 
             bufferFree(); 
           }; 
    }; 

    class xy_tcpip : xy_buffer { 
        public:
            int handle = 0; 
            long timeout = 0; 
            char rw = 'r'; 
            void (*fCallback)( xy_tcpip *xtcp, unsigned long seq ) = NULL; 
    }; 


#endif 
