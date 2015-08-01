DIST_SUBDIRS = secp256k1
AM_LDFLAGS = $(PTHREAD_CFLAGS) $(LIBTOOL_LDFLAGS)


if EMBEDDED_LEVELDB
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/include
LEVELDB_CPPFLAGS += -I$(srcdir)/leveldb/helpers/memenv
LIBLEVELDB += $(builddir)/leveldb/libleveldb.a
LIBMEMENV  += $(builddir)/leveldb/libmemenv.a

# NOTE: This dependency is not strictly necessary, but without it make may try to build both in parallel, which breaks the LevelDB build system in a race
$(LIBLEVELDB): $(LIBMEMENV)

$(LIBLEVELDB) $(LIBMEMENV):
	@echo "Building LevelDB ..." && $(MAKE) -C $(@D) $(@F) CXX="$(CXX)" \
	  CC="$(CC)" PLATFORM=$(TARGET_OS) AR="$(AR)" $(LEVELDB_TARGET_FLAGS) \
          OPT="$(CXXFLAGS) $(CPPFLAGS) -D__STDC_LIMIT_MACROS"
endif

KCOIN_CONFIG_INCLUDES=-I$(builddir)/config
KCOIN_INCLUDES=-I$(builddir) -I$(builddir)/obj $(BOOST_CPPFLAGS) $(LEVELDB_CPPFLAGS) $(CRYPTO_CFLAGS) $(SSL_CFLAGS)

KCOIN_INCLUDES += -I$(srcdir)/secp256k1/include

LIBKCOIN_SERVER=libkcoin_server.a
LIBKCOIN_WALLET=libkcoin_wallet.a
LIBKCOIN_COMMON=libkcoin_common.a
LIBKCOIN_CLI=libkcoin_cli.a
LIBKCOIN_UTIL=libkcoin_util.a
LIBKCOIN_CRYPTO=crypto/libkcoin_crypto.a
LIBKCOIN_UNIVALUE=univalue/libkcoin_univalue.a
LIBKCOINQT=qt/libkcoinqt.a
LIBSECP256K1=secp256k1/libsecp256k1.la

$(LIBSECP256K1): $(wildcard secp256k1/src/*) $(wildcard secp256k1/include/*)
	$(AM_V_at)$(MAKE) $(AM_MAKEFLAGS) -C $(@D) $(@F)

# Make is not made aware of per-object dependencies to avoid limiting building parallelization
# But to build the less dependent modules first, we manually select their order here:
EXTRA_LIBRARIES = \
  crypto/libkcoin_crypto.a \
  libkcoin_util.a \
  libkcoin_common.a \
  univalue/libkcoin_univalue.a \
  libkcoin_server.a \
  libkcoin_cli.a
if ENABLE_WALLET
KCOIN_INCLUDES += $(BDB_CPPFLAGS)
EXTRA_LIBRARIES += libkcoin_wallet.a
endif

if BUILD_KCOIN_LIBS
lib_LTLIBRARIES = libkcoinconsensus.la
LIBKCOIN_CONSENSUS=libkcoinconsensus.la
else
LIBKCOIN_CONSENSUS=
endif

bin_PROGRAMS =
TESTS =

if BUILD_KCOIND
  bin_PROGRAMS += kcoind
endif

if BUILD_KCOIN_UTILS
  bin_PROGRAMS += kcoin-cli kcoin-tx
endif

.PHONY: FORCE
# kcoin core #
KCOIN_CORE_H = \
  addrman.h \
  alert.h \
  auxpow.h \
  amount.h \
  arith_uint256.h \
  base58.h \
  bloom.h \
  chain.h \
  chainparams.h \
  chainparamsbase.h \
  chainparamsseeds.h \
  checkpoints.h \
  checkqueue.h \
  clientversion.h \
  coincontrol.h \
  coins.h \
  compat.h \
  compat/byteswap.h \
  compat/endian.h \
  compat/sanity.h \
  compressor.h \
  consensus/consensus.h \
  consensus/params.h \
  consensus/validation.h \
  core_io.h \
  core_memusage.h \
  eccryptoverify.h \
  ecwrapper.h \
  hash.h \
  init.h \
  key.h \
  keystore.h \
  leveldbwrapper.h \
  limitedmap.h \
  main.h \
  memusage.h \
  merkleblock.h \
  miner.h \
  mruset.h \
  net.h \
  netbase.h \
  noui.h \
  policy/fees.h \
  policy/policy.h \
  pow.h \
  primitives/block.h \
  primitives/pureheader.h \
  primitives/transaction.h \
  protocol.h \
  pubkey.h \
  random.h \
  rpcclient.h \
  rpcprotocol.h \
  rpcserver.h \
  scheduler.h \
  script/interpreter.h \
  script/script.h \
  script/script_error.h \
  script/sigcache.h \
  script/sign.h \
  script/standard.h \
  serialize.h \
  streams.h \
  support/allocators/secure.h \
  support/allocators/zeroafterfree.h \
  support/cleanse.h \
  support/pagelocker.h \
  sync.h \
  threadsafety.h \
  timedata.h \
  tinyformat.h \
  txdb.h \
  txmempool.h \
  ui_interface.h \
  uint256.h \
  undo.h \
  util.h \
  utilmoneystr.h \
  utilstrencodings.h \
  utiltime.h \
  validationinterface.h \
  version.h \
  wallet/crypter.h \
  wallet/db.h \
  wallet/wallet.h \
  wallet/wallet_ismine.h \
  wallet/walletdb.h

obj/build.h: FORCE
	@$(MKDIR_P) $(builddir)/obj
	@$(top_srcdir)/share/genbuild.sh $(abs_top_builddir)/src/obj/build.h \
	  $(abs_top_srcdir)
libkcoin_util_a-clientversion.$(OBJEXT): obj/build.h

# server: shared between kcoind and kcoin-qt
libkcoin_server_a_CPPFLAGS = $(KCOIN_INCLUDES) $(MINIUPNPC_CPPFLAGS)
libkcoin_server_a_SOURCES = \
  addrman.cpp \
  alert.cpp \
  bloom.cpp \
  chain.cpp \
  checkpoints.cpp \
  init.cpp \
  leveldbwrapper.cpp \
  main.cpp \
  merkleblock.cpp \
  miner.cpp \
  net.cpp \
  noui.cpp \
  policy/fees.cpp \
  policy/policy.cpp \
  pow.cpp \
  rest.cpp \
  rpcblockchain.cpp \
  rpcmining.cpp \
  rpcmisc.cpp \
  rpcnet.cpp \
  rpcrawtransaction.cpp \
  rpcserver.cpp \
  script/sigcache.cpp \
  timedata.cpp \
  txdb.cpp \
  txmempool.cpp \
  validationinterface.cpp \
  $(KCOIN_CORE_H)

# wallet: shared between kcoind and kcoin-qt, but only linked
# when wallet enabled
libkcoin_wallet_a_CPPFLAGS = $(KCOIN_INCLUDES)
libkcoin_wallet_a_SOURCES = \
  wallet/crypter.cpp \
  wallet/db.cpp \
  wallet/rpcdump.cpp \
  wallet/rpcwallet.cpp \
  wallet/wallet.cpp \
  wallet/wallet_ismine.cpp \
  wallet/walletdb.cpp \
  $(KCOIN_CORE_H)

# crypto primitives library
crypto_libkcoin_crypto_a_CPPFLAGS = $(KCOIN_CONFIG_INCLUDES)
crypto_libkcoin_crypto_a_SOURCES = \
  crypto/common.h \
  crypto/hmac_sha256.cpp \
  crypto/hmac_sha256.h \
  crypto/hmac_sha512.cpp \
  crypto/hmac_sha512.h \
  crypto/ripemd160.cpp \
  crypto/ripemd160.h \
  crypto/sha1.cpp \
  crypto/sha1.h \
  crypto/sha256.cpp \
  crypto/sha256.h \
  crypto/sha512.cpp \
  crypto/sha512.h

# univalue JSON library
univalue_libkcoin_univalue_a_SOURCES = \
  univalue/univalue.cpp \
  univalue/univalue.h \
  univalue/univalue_escapes.h \
  univalue/univalue_read.cpp \
  univalue/univalue_write.cpp

# common: shared between kcoind, and kcoin-qt and non-server tools
libkcoin_common_a_CPPFLAGS = $(KCOIN_INCLUDES)
libkcoin_common_a_SOURCES = \
  amount.cpp \
  arith_uint256.cpp \
  auxpow.cpp \
  base58.cpp \
  chainparams.cpp \
  coins.cpp \
  compressor.cpp \
  core_read.cpp \
  core_write.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  key.cpp \
  keystore.cpp \
  netbase.cpp \
  primitives/block.cpp \
  primitives/pureheader.cpp \
  primitives/transaction.cpp \
  protocol.cpp \
  pubkey.cpp \
  scheduler.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  script/script_error.cpp \
  script/sign.cpp \
  script/standard.cpp \
  $(KCOIN_CORE_H)

# util: shared between all executables.
# This library *must* be included to make sure that the glibc
# backward-compatibility objects and their sanity checks are linked.
libkcoin_util_a_CPPFLAGS = $(KCOIN_INCLUDES)
libkcoin_util_a_SOURCES = \
  support/pagelocker.cpp \
  chainparamsbase.cpp \
  clientversion.cpp \
  compat/glibc_sanity.cpp \
  compat/glibcxx_sanity.cpp \
  compat/strnlen.cpp \
  random.cpp \
  rpcprotocol.cpp \
  support/cleanse.cpp \
  sync.cpp \
  uint256.cpp \
  util.cpp \
  utilmoneystr.cpp \
  utilstrencodings.cpp \
  utiltime.cpp \
  $(KCOIN_CORE_H)

if GLIBC_BACK_COMPAT
libkcoin_util_a_SOURCES += compat/glibc_compat.cpp
endif

# cli: shared between kcoin-cli and kcoin-qt
libkcoin_cli_a_CPPFLAGS = $(KCOIN_INCLUDES)
libkcoin_cli_a_SOURCES = \
  rpcclient.cpp \
  $(KCOIN_CORE_H)

nodist_libkcoin_util_a_SOURCES = $(srcdir)/obj/build.h
#

# kcoind binary #
kcoind_SOURCES = kcoind.cpp
kcoind_CPPFLAGS = $(KCOIN_INCLUDES)
kcoind_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
kcoind_SOURCES += kcoind-res.rc
endif

kcoind_LDADD = \
  $(LIBKCOIN_SERVER) \
  $(LIBKCOIN_COMMON) \
  $(LIBKCOIN_UNIVALUE) \
  $(LIBKCOIN_UTIL) \
  $(LIBKCOIN_CRYPTO) \
  $(LIBLEVELDB) \
  $(LIBMEMENV) \
  $(LIBSECP256K1)

if ENABLE_WALLET
kcoind_LDADD += libkcoin_wallet.a
endif

kcoind_LDADD += $(BOOST_LIBS) $(BDB_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS) $(MINIUPNPC_LIBS)
#

# kcoin-cli binary #
kcoin_cli_SOURCES = kcoin-cli.cpp
kcoin_cli_CPPFLAGS = $(KCOIN_INCLUDES)
kcoin_cli_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
kcoin_cli_SOURCES += kcoin-cli-res.rc
endif

kcoin_cli_LDADD = \
  $(LIBKCOIN_CLI) \
  $(LIBKCOIN_UNIVALUE) \
  $(LIBKCOIN_UTIL) \
  $(LIBSECP256K1)

kcoin_cli_LDADD += $(BOOST_LIBS) $(SSL_LIBS) $(CRYPTO_LIBS)
#

# kcoin-tx binary #
kcoin_tx_SOURCES = kcoin-tx.cpp
kcoin_tx_CPPFLAGS = $(KCOIN_INCLUDES)
kcoin_tx_LDFLAGS = $(RELDFLAGS) $(AM_LDFLAGS) $(LIBTOOL_APP_LDFLAGS)

if TARGET_WINDOWS
kcoin_tx_SOURCES += kcoin-tx-res.rc
endif

kcoin_tx_LDADD = \
  $(LIBKCOIN_UNIVALUE) \
  $(LIBKCOIN_COMMON) \
  $(LIBKCOIN_UTIL) \
  $(LIBKCOIN_CRYPTO) \
  $(LIBSECP256K1)

kcoin_tx_LDADD += $(BOOST_LIBS) $(CRYPTO_LIBS)
#

# kcoinconsensus library #
if BUILD_KCOIN_LIBS
include_HEADERS = script/kcoinconsensus.h
libkcoinconsensus_la_SOURCES = \
  crypto/hmac_sha512.cpp \
  crypto/ripemd160.cpp \
  crypto/sha1.cpp \
  crypto/sha256.cpp \
  crypto/sha512.cpp \
  eccryptoverify.cpp \
  ecwrapper.cpp \
  hash.cpp \
  primitives/transaction.cpp \
  pubkey.cpp \
  script/kcoinconsensus.cpp \
  script/interpreter.cpp \
  script/script.cpp \
  uint256.cpp \
  utilstrencodings.cpp

if GLIBC_BACK_COMPAT
  libkcoinconsensus_la_SOURCES += compat/glibc_compat.cpp
endif

libkcoinconsensus_la_LDFLAGS = -no-undefined $(RELDFLAGS)
libkcoinconsensus_la_LIBADD = $(CRYPTO_LIBS)
libkcoinconsensus_la_CPPFLAGS = $(CRYPTO_CFLAGS) -I$(builddir)/obj -DBUILD_KCOIN_INTERNAL

endif
#

CLEANFILES = leveldb/libleveldb.a leveldb/libmemenv.a *.gcda *.gcno

DISTCLEANFILES = obj/build.h

EXTRA_DIST = leveldb

clean-local:
	-$(MAKE) -C leveldb clean
	-$(MAKE) -C secp256k1 clean
	rm -f leveldb/*/*.gcno leveldb/helpers/memenv/*.gcno
	-rm -f config.h

.rc.o:
	@test -f $(WINDRES)
	$(AM_V_GEN) $(WINDRES) -DWINDRES_PREPROC -i $< -o $@

.mm.o:
	$(AM_V_CXX) $(OBJCXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	  $(CPPFLAGS) $(AM_CXXFLAGS) $(QT_INCLUDES) $(CXXFLAGS)  -c -o $@ $<

%.pb.cc %.pb.h: %.proto
	@test -f $(PROTOC)
	$(AM_V_GEN) $(PROTOC) --cpp_out=$(@D) --proto_path=$(abspath $(<D) $<)

if ENABLE_TESTS
include Makefile.test.include
endif

if ENABLE_QT
include Makefile.qt.include
endif

if ENABLE_QT_TESTS
include Makefile.qttest.include
endif
