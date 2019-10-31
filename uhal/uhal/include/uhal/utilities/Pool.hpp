
#include <list>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>

namespace uhal
{


  template < typename T , bool ThreadSafe >
  class Pool;


  template < typename T >
  class Pool< T , false >
  {
  public:

    typedef typename std::list< T >::iterator iterator;

    Pool()
    {}

    virtual ~Pool()
    {}

    void claim( iterator& aIterator , bool& aFresh )
    {
      if( mFree.empty() )
      {
        mUsed.push_front( T() );
        aIterator = mUsed.begin();
        aFresh = true;
      } else {
        aIterator = mFree.begin();
        mUsed.splice( mUsed.end() , mFree , aIterator );
        aFresh = false;
      }
    }

    void release( iterator& aIterator )
    {
      mFree.splice( mFree.end() , mUsed , aIterator );
    }

  private:
    std::list< T > mFree;
    std::list< T > mUsed;
  };


  template < typename T >
  class Pool< T , true >
  {
  public:

    typedef typename std::list< T >::iterator iterator;

    Pool()
    {}

    virtual ~Pool()
    {}

    void claim( iterator& aIterator , bool& aFresh )
    {
      boost::lock_guard<boost::mutex> lLock ( mMutex );
      if( mFree.empty() )
      {
        mUsed.push_front( T() );
        aIterator = mUsed.begin();
        aFresh = true;
      } else {
        aIterator = mFree.begin();
        mUsed.splice( mUsed.end() , mFree , aIterator );
        aFresh = false;
      }
    }

    void release( iterator& aIterator )
    {
      boost::lock_guard<boost::mutex> lLock ( mMutex );
      mFree.splice( mFree.end() , mUsed , aIterator );
    }

  private:
    std::list< T > mFree;
    std::list< T > mUsed;
    boost::mutex mMutex;  
  };



}