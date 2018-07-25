 /*************************************************************************
 * 
 *  [2017] - [2018] Automy Inc. 
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of Automy Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Automy Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Automy Incorporated.
 */

#ifndef INCLUDE_VNX_VISITOR_H_
#define INCLUDE_VNX_VISITOR_H_

#include <vnx/Type.h>


namespace vnx {

/*
 * A Visitor is used to traverse any type in a generic manner.
 */
class Visitor {
public:
	virtual ~Visitor() {}
	
	virtual void visit_null() {}
	virtual void visit(const bool_t& value) {}
	virtual void visit(const uint8_t& value) {}
	virtual void visit(const uint16_t& value) {}
	virtual void visit(const uint32_t& value) {}
	virtual void visit(const uint64_t& value) {}
	virtual void visit(const int8_t& value) {}
	virtual void visit(const int16_t& value) {}
	virtual void visit(const int32_t& value) {}
	virtual void visit(const int64_t& value) {}
	virtual void visit(const float32_t& value) {}
	virtual void visit(const float64_t& value) {}
	virtual void visit(const std::string& value) {}
	
	virtual void list_begin(size_t size) {}
	virtual void list_element(size_t index) {}
	virtual void list_end(size_t size) {}
	
	virtual void map_begin(size_t size) {}
	virtual void map_entry_begin(size_t index) {}
	virtual void map_entry_value(size_t index) {}
	virtual void map_entry_end(size_t index) {}
	virtual void map_end(size_t size) {}
	
	virtual void type_begin(const TypeCode& type) {}
	virtual void type_field(const TypeField& field, size_t index) {}
	virtual void type_end(const TypeCode& type) {}
	
	virtual void enum_value(uint32_t value, const std::string& name) {}
	
};


inline void accept(Visitor& vistor, const bool_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const uint8_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const uint16_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const uint32_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const uint64_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const int8_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const int16_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const int32_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const int64_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const float32_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const float64_t& value) { vistor.visit(value); }
inline void accept(Visitor& vistor, const std::string& value) { vistor.visit(value); }

template<typename T, size_t N>
void accept(Visitor& vistor, const std::array<T, N>& array) {
	vistor.list_begin(N);
	for(size_t i = 0; i < N; ++i) {
		vistor.list_element(i);
		vnx::type<T>().accept(vistor, array[i]);
	}
	vistor.list_end(N);
}

template<typename T>
void accept(Visitor& vistor, const std::vector<T>& vector) {
	vistor.list_begin(vector.size());
	for(size_t i = 0; i < vector.size(); ++i) {
		vistor.list_element(i);
		vnx::type<T>().accept(vistor, vector[i]);
	}
	vistor.list_end(vector.size());
}

template<typename K, typename V>
void accept(Visitor& vistor, const std::map<K, V>& map) {
	vistor.map_begin(map.size());
	size_t i = 0;
	for(const auto& entry : map) {
		vistor.map_entry_begin(i);
		vnx::type<K>().accept(vistor, entry.first);
		vistor.map_entry_value(i);
		vnx::type<V>().accept(vistor, entry.second);
		vistor.map_entry_end(i);
		i++;
	}
	vistor.map_end(map.size());
}

void accept(Visitor& vistor, const Value& value);

void accept(Visitor& visitor, TypeInput& in, const TypeCode* type_code = 0, const uint16_t* code = 0);

template<typename T>
void accept(Visitor& vistor, const std::shared_ptr<T>& value) {
	if(value) {
		accept(vistor, *value);
	} else {
		vistor.visit_null();
	}
}

template<typename T>
void type<T>::accept(Visitor& visitor, const T& value) {
	vnx::accept(visitor, value);
}


} // vnx

#endif /* INCLUDE_VNX_VISITOR_H_ */
