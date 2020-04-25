#include<bits/stdc++.h>
using namespace std;

#define END_OF_FILE 256

class output_code_stream
{
public :
    output_code_stream( std::ostream &output, unsigned int max_code ) 
        : m_output( output ),
          m_pending_bits(0),
          m_pending_output(0),
          m_code_size(9),
          m_current_code(256),
          m_next_bump(512),
          m_max_code(max_code)
    {}
  
    void operator<<( const unsigned int &i )
    {
        m_pending_output |= i << m_pending_bits;
        m_pending_bits += m_code_size;
        if(i == END_OF_FILE)
        	flush(0);
        else
			flush(8);	
        if ( m_current_code < m_max_code ) {
            m_current_code++;
            if ( m_current_code == m_next_bump ) {
                m_next_bump *= 2;
                m_code_size++;
            }
        }
    }
private :
    void flush( const int val )
    {
        while ( m_pending_bits >= val ) {
            m_output.put( m_pending_output & 0xff );
            m_pending_output >>= 8;
            m_pending_bits -= 8;
        }
    }
    int m_code_size;
    std::ostream & m_output;
    int m_pending_bits;
    unsigned int m_pending_output;
    unsigned int m_current_code;
    unsigned int m_next_bump;
    unsigned int m_max_code;
};

class input_code_stream
{
public :
    input_code_stream( std::istream &input, unsigned int max_code ) 
        : m_input( input ),
          m_available_bits(0),
          m_pending_input(0),
          m_code_size(9),
          m_current_code(256),
          m_next_bump(512),
          m_max_code( max_code )
    {}
    bool operator>>( unsigned int &i )
    {
        while ( m_available_bits < m_code_size )
        {
            char c;
            if ( !m_input.get(c) )
                return false;
            m_pending_input |= (c & 0xff) << m_available_bits;
            m_available_bits += 8;
        }
        i = m_pending_input & ~(~0 << m_code_size);
        m_pending_input >>= m_code_size;
        m_available_bits -= m_code_size;
        if ( m_current_code < m_max_code ) {
            m_current_code++;
            if ( m_current_code == m_next_bump ) {
                m_next_bump *= 2;
                m_code_size++;
            }
        }
        if ( i == END_OF_FILE)
            return false;
        else
            return true;
    }
private :
    int m_code_size;
    std::istream & m_input;
    int m_available_bits;
    unsigned int m_pending_input;
    unsigned int m_current_code;
    unsigned int m_next_bump;
    unsigned int m_max_code;
};


 //namespace lzw

