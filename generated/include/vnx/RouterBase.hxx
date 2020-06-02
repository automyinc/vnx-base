
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_RouterBase_HXX_
#define INCLUDE_vnx_RouterBase_HXX_

#include <vnx/package.hxx>
#include <vnx/Module.h>


namespace vnx {

class RouterBase : public ::vnx::Module {
public:
	
	int32_t port = 4444;
	std::string unix_path = ".vnxrouter.sock";
	int32_t max_queue_ms = 100;
	std::map<std::string, std::vector<std::string>> import_map;
	std::map<std::string, std::vector<std::string>> export_map;
	std::vector<std::string> export_list;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	RouterBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const;
	const char* get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	friend std::ostream& operator<<(std::ostream& _out, const RouterBase& _value);
	friend std::istream& operator>>(std::istream& _in, RouterBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Sample> _sample) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _value, const vnx::request_id_t& _request_id) override;
	
private:
	
};


} // namespace vnx

#endif // INCLUDE_vnx_RouterBase_HXX_
