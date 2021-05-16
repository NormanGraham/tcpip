// xy_tcpip.h 

#ifndef xy_tcpip_h 
#define xy_tcpip_h 
   
    class xy_buffer { 
       public: 
           char *ptrb = NULL; 
           unsigned short allocated = 0;
           unsigned short ip = 0;
           unsigned errorCount = 0; 
       
           void bShallowCopy( xy_buffer *xy ) { 
              ptrb = xy->ptrb; 
              allocated = xy->allocated; 
              ip = xy->ip;
              // does not copy errorCount.
           }; 
       
           void Set( int offset, unsigned char *src, unsigned short len ) {
              if ( offset < 0 ) 
                 errorCount++; 
              else {
                   unsigned A = allocated; 
                   unsigned char *tmpPtr = ptrb; 
                   for (; (A) && (offset); offset--, A--, tmpPtr++ )
                      ; 
                   if ( !A ) { 
                      errorCount++; 
                   } 
                   else { 
                      memcpy( tmpPtr, src, len > A ? A : len );   
                   }                     
              }
           }; 
           void bAllocate( unsigned short A ) { 
                   if ( ptrb )  
                     delete [] ptrb;
                   ptrb  = NULL;
                   ip = 0; 
                   allocated = 0; 
                   if ( A < (16*1024) ) {    // use the arbitrary 16k max.  
                      ptrb = new unsigned char[ A + 1 ];
                      memset(ptrb, 0, A+1); 
                      allocated = A;
                   }
                   else 
                      errorCount++; 
           }; 
           void bufferFree() { 
                 if ( ptrb ) {
                   delete [] ptrb ;
                   ptrb = NULL; 
                 }
                 allocated = 0; 
                 ip = 0;
           };
           void prefix( xy_buffer *xb) {
              xy_buffer newxy;
              newxy.bufferAllocate ( allocated + xb.allocated) ; 
                    
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
