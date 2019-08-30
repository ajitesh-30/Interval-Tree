#include <map>
#include <limits>

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

    	if (!(keyBegin<keyEnd))
    	{
    		return;
    	}

    	// Get index of first element having value greater than keyEnd
    	auto nextInterval = --m_map.upper_bound(keyEnd);

    	auto lbBegin = m_map.end();
    	auto ubBegin = m_map.end();

    	assert(nextInterval!=m_map.end());


    	if (nextInterval->second==val){
    		nextInterval = nextInterval+1;
    	}
    	else if(nextInterval->first<keyEnd){
    		const V & nextValue = nextInterval.second;
    		++nextInterval;
    		inserted1 = nextInterval = m_map.emplace(nextInterval,keyEnd,nextValue);
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
// the interval_map, for example using a map of unsigned int intervals to char.