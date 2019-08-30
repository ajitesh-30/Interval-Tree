#include <assert.h>
#include <map>
#include <limits>
#include <iostream>
#include <random>

template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;

public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {

    	if (!(keyBegin < keyEnd))
            return;
     	
     	V valend;
     	bool x = true;
     	auto lbBegin = m_map.lower_bound(keyBegin);
     	auto lbEnd = m_map.lower_bound(keyBegin);

     	if(lbBegin!=m_map.end() && lbBegin->first==keyBegin){
     		valend = lbBegin->second;
     		lbBegin->second = val;
     		++lbEnd;
     		if(lbEnd==m_map.end()){
     			x = false;
     		}
     	}
     	else{
     		auto upBegin = lbBegin;
     		--upBegin;
     		valend = upBegin->second;
     		if(upBegin->second!=val){
     			auto it = m_map.insert(lbBegin,std::make_pair(keyBegin,val));
     			lbBegin = it;
     			lbEnd = ++it;
     		}
     	}

     	auto upEnd = m_map.lower_bound(keyEnd);
     	auto upDelete = upEnd;

     	if(upDelete==lbEnd){
     		x=false;
     	}
     	if(upEnd==m_map.end() || upEnd->first!=keyEnd)
     	{
     		auto prev = upEnd;
     		--prev;
     		if(prev!=lbBegin)
     		{
     			valend = prev->second;
     		}
     		if(valend!=val)
     		{
     			auto it = m_map.insert(upEnd,std::make_pair(keyEnd,valend));
     			upDelete=it;
     			if((++it)!=m_map.end() && it->second==valend)
     			{
     				 m_map.erase(it);
     			}
     		}
     	}
     	if(x && lbEnd!=m_map.end() && upDelete!=m_map.end() && lbEnd->first < upDelete->first)
     	{
     		m_map.erase(lbEnd,upDelete);
     	}
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
