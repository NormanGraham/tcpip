// xy_tcpip.h 

#ifndef xy_tcpip_h 
#define xy_tcpip_h 
   
    class xy_buffer { 
       public: 
           unsigned char *ptrb = NULL; 
           unsigned short allocated = 0;
           unsigned short ip = 0;
           unsigned errorCount = 0; 
           static unsigned short MaxBufferSize = 16 * 1024; 
       
           xy_buffer ( const xy_buffer *xy1, const xy_buffer *xy2 ) { 
               allocated = xy1->allocated + xy2->allocated; 
               if ( allocated > MaxBufferSize ) {
                  allocated = 0; 
                  errorCount++; 
               } 
               else { 
                 ptrb = new unsigned char [allocated]; 
                 memset(ptrb, 0, allocated); 
                 unsigned char *b = ptrb; 
                 memcpy( b, xy1->ptr, xy1->allocated);
                 b+= xy1->allocated; 
                 memcpy( b, xy2->ptr, xy2->allocated); 
           }; 
       
           void Set( int offset, unsigned char *src, unsigned short len ) {
              if ( offset < 0 ) 
                 errorCount++; 
              else {
                   unsigned A = allocated; 
                   unsigned char *tmpPtr = ptrb; 
                   for (; (A) && (offset); offset--, A--, tmpPtr++ )
                      ; 
                   if ( !A && (len) ) { 
                      errorCount++; 
                   } 
                   else { 
                      memcpy( tmpPtr, src, len > A ? A : len );   
                   }                     
           }; 
           
           xy_buffer ( const unsigned char *p, unsigned short len ) {
              if ( len > MaxBufferSize ) { 
                 errorCount++; 
              } 
              else {
                 ptrb = new unsigned char [ len ]; 
                 memcpy( ptrb, p, len ); 
                 allocated = len;
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
                   // create a new buffer, copy both into, copy both buffers into tmp, then 
              xy_buffer newxy;
              newxy.bufferAllocate ( allocated + xb.allocated) ; 
              newxy.Set(0, xb->ptrb, xb->len ); 
              newxy.Set(xb->len, ptrb, len); 
              bShallowCopy( newxy ); 
              newxy.ptrb = NULL; // *this, now owns pointer, after shallow copy.
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
