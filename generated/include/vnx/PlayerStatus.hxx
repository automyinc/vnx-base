
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_PlayerStatus_HXX_
#define INCLUDE_vnx_PlayerStatus_HXX_

#include <vnx/package.hxx>
#include <vnx/RecordHeader.hxx>
#include <vnx/TimeControl.hxx>
#include <vnx/Value.h>


namespace vnx {

class PlayerStatus : public ::vnx::Value {
public:
	
	std::string filename;
	int64_t begin_time = 0;
	int64_t end_time = 0;
	int64_t current_time = 0;
	vnx::float64_t progress = 0;
	vnx::float64_t actual_speed = 0;
	vnx::float64_t bandwidth = 0;
	vnx::float64_t sample_rate = 0;
	std::string message;
	::vnx::TimeControl control;
	::vnx::RecordHeader info;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x7356e9a5699a79ebull;
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<PlayerStatus> create();
	std::shared_ptr<vnx::Value> clone() const override;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) override;
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const PlayerStatus& _value);
	friend std::istream& operator>>(std::istream& _in, PlayerStatus& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace vnx


namespace vnx {

} // vnx

#endif // INCLUDE_vnx_PlayerStatus_HXX_
