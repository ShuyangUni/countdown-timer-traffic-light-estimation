// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hsmm_parameter.proto

#include "hsmm_parameter.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace cttl {
namespace hsmm {
PROTOBUF_CONSTEXPR HSMMParameterProto::HSMMParameterProto(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.str_file_distribution_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.hz_)*/0
  , /*decltype(_impl_.res_)*/0
  , /*decltype(_impl_.d_)*/0
  , /*decltype(_impl_.sigma_)*/0
  , /*decltype(_impl_.max_n_)*/0
  , /*decltype(_impl_.n_state_)*/0
  , /*decltype(_impl_.alpha_)*/0
  , /*decltype(_impl_.n_obs_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct HSMMParameterProtoDefaultTypeInternal {
  PROTOBUF_CONSTEXPR HSMMParameterProtoDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~HSMMParameterProtoDefaultTypeInternal() {}
  union {
    HSMMParameterProto _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 HSMMParameterProtoDefaultTypeInternal _HSMMParameterProto_default_instance_;
}  // namespace hsmm
}  // namespace cttl
static ::_pb::Metadata file_level_metadata_hsmm_5fparameter_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_hsmm_5fparameter_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_hsmm_5fparameter_2eproto = nullptr;

const uint32_t TableStruct_hsmm_5fparameter_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.hz_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.res_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.d_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.sigma_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.max_n_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.n_state_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.n_obs_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.alpha_),
  PROTOBUF_FIELD_OFFSET(::cttl::hsmm::HSMMParameterProto, _impl_.str_file_distribution_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::cttl::hsmm::HSMMParameterProto)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::cttl::hsmm::_HSMMParameterProto_default_instance_._instance,
};

const char descriptor_table_protodef_hsmm_5fparameter_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\024hsmm_parameter.proto\022\tcttl.hsmm\"\244\001\n\022HS"
  "MMParameterProto\022\n\n\002hz\030\001 \001(\001\022\013\n\003res\030\002 \001("
  "\001\022\t\n\001d\030\003 \001(\001\022\r\n\005sigma\030\004 \001(\001\022\r\n\005max_n\030\005 \001"
  "(\005\022\017\n\007n_state\030\006 \001(\005\022\r\n\005n_obs\030\007 \001(\005\022\r\n\005al"
  "pha\030\010 \001(\001\022\035\n\025str_file_distribution\030\t \001(\t"
  "b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_hsmm_5fparameter_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_hsmm_5fparameter_2eproto = {
    false, false, 208, descriptor_table_protodef_hsmm_5fparameter_2eproto,
    "hsmm_parameter.proto",
    &descriptor_table_hsmm_5fparameter_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_hsmm_5fparameter_2eproto::offsets,
    file_level_metadata_hsmm_5fparameter_2eproto, file_level_enum_descriptors_hsmm_5fparameter_2eproto,
    file_level_service_descriptors_hsmm_5fparameter_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_hsmm_5fparameter_2eproto_getter() {
  return &descriptor_table_hsmm_5fparameter_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_hsmm_5fparameter_2eproto(&descriptor_table_hsmm_5fparameter_2eproto);
namespace cttl {
namespace hsmm {

// ===================================================================

class HSMMParameterProto::_Internal {
 public:
};

HSMMParameterProto::HSMMParameterProto(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:cttl.hsmm.HSMMParameterProto)
}
HSMMParameterProto::HSMMParameterProto(const HSMMParameterProto& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  HSMMParameterProto* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.str_file_distribution_){}
    , decltype(_impl_.hz_){}
    , decltype(_impl_.res_){}
    , decltype(_impl_.d_){}
    , decltype(_impl_.sigma_){}
    , decltype(_impl_.max_n_){}
    , decltype(_impl_.n_state_){}
    , decltype(_impl_.alpha_){}
    , decltype(_impl_.n_obs_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.str_file_distribution_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.str_file_distribution_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_str_file_distribution().empty()) {
    _this->_impl_.str_file_distribution_.Set(from._internal_str_file_distribution(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.hz_, &from._impl_.hz_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.n_obs_) -
    reinterpret_cast<char*>(&_impl_.hz_)) + sizeof(_impl_.n_obs_));
  // @@protoc_insertion_point(copy_constructor:cttl.hsmm.HSMMParameterProto)
}

inline void HSMMParameterProto::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.str_file_distribution_){}
    , decltype(_impl_.hz_){0}
    , decltype(_impl_.res_){0}
    , decltype(_impl_.d_){0}
    , decltype(_impl_.sigma_){0}
    , decltype(_impl_.max_n_){0}
    , decltype(_impl_.n_state_){0}
    , decltype(_impl_.alpha_){0}
    , decltype(_impl_.n_obs_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.str_file_distribution_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.str_file_distribution_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

HSMMParameterProto::~HSMMParameterProto() {
  // @@protoc_insertion_point(destructor:cttl.hsmm.HSMMParameterProto)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void HSMMParameterProto::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.str_file_distribution_.Destroy();
}

void HSMMParameterProto::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void HSMMParameterProto::Clear() {
// @@protoc_insertion_point(message_clear_start:cttl.hsmm.HSMMParameterProto)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.str_file_distribution_.ClearToEmpty();
  ::memset(&_impl_.hz_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.n_obs_) -
      reinterpret_cast<char*>(&_impl_.hz_)) + sizeof(_impl_.n_obs_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* HSMMParameterProto::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // double hz = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 9)) {
          _impl_.hz_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // double res = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 17)) {
          _impl_.res_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // double d = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 25)) {
          _impl_.d_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // double sigma = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 33)) {
          _impl_.sigma_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // int32 max_n = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 40)) {
          _impl_.max_n_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 n_state = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          _impl_.n_state_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 n_obs = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          _impl_.n_obs_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // double alpha = 8;
      case 8:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 65)) {
          _impl_.alpha_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
        } else
          goto handle_unusual;
        continue;
      // string str_file_distribution = 9;
      case 9:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 74)) {
          auto str = _internal_mutable_str_file_distribution();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "cttl.hsmm.HSMMParameterProto.str_file_distribution"));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* HSMMParameterProto::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:cttl.hsmm.HSMMParameterProto)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // double hz = 1;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_hz = this->_internal_hz();
  uint64_t raw_hz;
  memcpy(&raw_hz, &tmp_hz, sizeof(tmp_hz));
  if (raw_hz != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(1, this->_internal_hz(), target);
  }

  // double res = 2;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_res = this->_internal_res();
  uint64_t raw_res;
  memcpy(&raw_res, &tmp_res, sizeof(tmp_res));
  if (raw_res != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(2, this->_internal_res(), target);
  }

  // double d = 3;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_d = this->_internal_d();
  uint64_t raw_d;
  memcpy(&raw_d, &tmp_d, sizeof(tmp_d));
  if (raw_d != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(3, this->_internal_d(), target);
  }

  // double sigma = 4;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_sigma = this->_internal_sigma();
  uint64_t raw_sigma;
  memcpy(&raw_sigma, &tmp_sigma, sizeof(tmp_sigma));
  if (raw_sigma != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(4, this->_internal_sigma(), target);
  }

  // int32 max_n = 5;
  if (this->_internal_max_n() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(5, this->_internal_max_n(), target);
  }

  // int32 n_state = 6;
  if (this->_internal_n_state() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(6, this->_internal_n_state(), target);
  }

  // int32 n_obs = 7;
  if (this->_internal_n_obs() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(7, this->_internal_n_obs(), target);
  }

  // double alpha = 8;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_alpha = this->_internal_alpha();
  uint64_t raw_alpha;
  memcpy(&raw_alpha, &tmp_alpha, sizeof(tmp_alpha));
  if (raw_alpha != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteDoubleToArray(8, this->_internal_alpha(), target);
  }

  // string str_file_distribution = 9;
  if (!this->_internal_str_file_distribution().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_str_file_distribution().data(), static_cast<int>(this->_internal_str_file_distribution().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "cttl.hsmm.HSMMParameterProto.str_file_distribution");
    target = stream->WriteStringMaybeAliased(
        9, this->_internal_str_file_distribution(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:cttl.hsmm.HSMMParameterProto)
  return target;
}

size_t HSMMParameterProto::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:cttl.hsmm.HSMMParameterProto)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string str_file_distribution = 9;
  if (!this->_internal_str_file_distribution().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_str_file_distribution());
  }

  // double hz = 1;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_hz = this->_internal_hz();
  uint64_t raw_hz;
  memcpy(&raw_hz, &tmp_hz, sizeof(tmp_hz));
  if (raw_hz != 0) {
    total_size += 1 + 8;
  }

  // double res = 2;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_res = this->_internal_res();
  uint64_t raw_res;
  memcpy(&raw_res, &tmp_res, sizeof(tmp_res));
  if (raw_res != 0) {
    total_size += 1 + 8;
  }

  // double d = 3;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_d = this->_internal_d();
  uint64_t raw_d;
  memcpy(&raw_d, &tmp_d, sizeof(tmp_d));
  if (raw_d != 0) {
    total_size += 1 + 8;
  }

  // double sigma = 4;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_sigma = this->_internal_sigma();
  uint64_t raw_sigma;
  memcpy(&raw_sigma, &tmp_sigma, sizeof(tmp_sigma));
  if (raw_sigma != 0) {
    total_size += 1 + 8;
  }

  // int32 max_n = 5;
  if (this->_internal_max_n() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_max_n());
  }

  // int32 n_state = 6;
  if (this->_internal_n_state() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_n_state());
  }

  // double alpha = 8;
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_alpha = this->_internal_alpha();
  uint64_t raw_alpha;
  memcpy(&raw_alpha, &tmp_alpha, sizeof(tmp_alpha));
  if (raw_alpha != 0) {
    total_size += 1 + 8;
  }

  // int32 n_obs = 7;
  if (this->_internal_n_obs() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_n_obs());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData HSMMParameterProto::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    HSMMParameterProto::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*HSMMParameterProto::GetClassData() const { return &_class_data_; }


void HSMMParameterProto::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<HSMMParameterProto*>(&to_msg);
  auto& from = static_cast<const HSMMParameterProto&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:cttl.hsmm.HSMMParameterProto)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_str_file_distribution().empty()) {
    _this->_internal_set_str_file_distribution(from._internal_str_file_distribution());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_hz = from._internal_hz();
  uint64_t raw_hz;
  memcpy(&raw_hz, &tmp_hz, sizeof(tmp_hz));
  if (raw_hz != 0) {
    _this->_internal_set_hz(from._internal_hz());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_res = from._internal_res();
  uint64_t raw_res;
  memcpy(&raw_res, &tmp_res, sizeof(tmp_res));
  if (raw_res != 0) {
    _this->_internal_set_res(from._internal_res());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_d = from._internal_d();
  uint64_t raw_d;
  memcpy(&raw_d, &tmp_d, sizeof(tmp_d));
  if (raw_d != 0) {
    _this->_internal_set_d(from._internal_d());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_sigma = from._internal_sigma();
  uint64_t raw_sigma;
  memcpy(&raw_sigma, &tmp_sigma, sizeof(tmp_sigma));
  if (raw_sigma != 0) {
    _this->_internal_set_sigma(from._internal_sigma());
  }
  if (from._internal_max_n() != 0) {
    _this->_internal_set_max_n(from._internal_max_n());
  }
  if (from._internal_n_state() != 0) {
    _this->_internal_set_n_state(from._internal_n_state());
  }
  static_assert(sizeof(uint64_t) == sizeof(double), "Code assumes uint64_t and double are the same size.");
  double tmp_alpha = from._internal_alpha();
  uint64_t raw_alpha;
  memcpy(&raw_alpha, &tmp_alpha, sizeof(tmp_alpha));
  if (raw_alpha != 0) {
    _this->_internal_set_alpha(from._internal_alpha());
  }
  if (from._internal_n_obs() != 0) {
    _this->_internal_set_n_obs(from._internal_n_obs());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void HSMMParameterProto::CopyFrom(const HSMMParameterProto& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:cttl.hsmm.HSMMParameterProto)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool HSMMParameterProto::IsInitialized() const {
  return true;
}

void HSMMParameterProto::InternalSwap(HSMMParameterProto* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.str_file_distribution_, lhs_arena,
      &other->_impl_.str_file_distribution_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(HSMMParameterProto, _impl_.n_obs_)
      + sizeof(HSMMParameterProto::_impl_.n_obs_)
      - PROTOBUF_FIELD_OFFSET(HSMMParameterProto, _impl_.hz_)>(
          reinterpret_cast<char*>(&_impl_.hz_),
          reinterpret_cast<char*>(&other->_impl_.hz_));
}

::PROTOBUF_NAMESPACE_ID::Metadata HSMMParameterProto::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_hsmm_5fparameter_2eproto_getter, &descriptor_table_hsmm_5fparameter_2eproto_once,
      file_level_metadata_hsmm_5fparameter_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace hsmm
}  // namespace cttl
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::cttl::hsmm::HSMMParameterProto*
Arena::CreateMaybeMessage< ::cttl::hsmm::HSMMParameterProto >(Arena* arena) {
  return Arena::CreateMessageInternal< ::cttl::hsmm::HSMMParameterProto >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
