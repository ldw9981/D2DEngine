#pragma once
class ReferenceCounter {
private:
	unsigned int m_RefCount;  // Reference count

public:
	ReferenceCounter() : m_RefCount(0) { } 
	
	// virtual 키워드 사용으로 파괴자를 가상함수로 만들어 delete를 호출할때 
	// 파괴자를 호출이 자식의 파괴자 -> 부모의 파괴자 순으로 호출 되도록 한다.
	virtual ~ReferenceCounter() { }			

	unsigned int AddRef() {
		m_RefCount++;
		return m_RefCount;
	}

	unsigned int Release() {
		m_RefCount--;
		if (m_RefCount == 0) {
			delete this;
			return 0;
		}
		return m_RefCount;
	}

	unsigned int GetRefCount() {		
		return m_RefCount;
	}
};