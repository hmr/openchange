/* 
   Unix SMB/CIFS implementation.

   endpoint server for the exchange_* pipes

   Copyright (C) Julien Kerihuel 2005
   
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _DCESRV_EXCHANGE_H_
# define _DCESRV_EXCHANGE_H_

/* #include <auth.h> */

struct auth_serversupplied_info 
{
	struct dom_sid *account_sid;
	struct dom_sid *primary_group_sid;

	size_t n_domain_groups;
	struct dom_sid **domain_groups;

	DATA_BLOB user_session_key;
	DATA_BLOB lm_session_key;

	const char *account_name;
	const char *domain_name;

	const char *full_name;
	const char *logon_script;
	const char *profile_path;
	const char *home_directory;
	const char *home_drive;
	const char *logon_server;
	
	NTTIME last_logon;
	NTTIME last_logoff;
	NTTIME acct_expiry;
	NTTIME last_password_change;
	NTTIME allow_password_change;
	NTTIME force_password_change;

	uint16_t logon_count;
	uint16_t bad_password_count;

	uint32_t acct_flags;

	bool authenticated;
};


struct auth_session_info {
	struct security_token *security_token;
	struct auth_serversupplied_info *server_info;
	DATA_BLOB session_key;
	struct cli_credentials *credentials;
};

#define	NTLM_AUTH_IS_OK(dce_call) \
(dce_call->conn->auth_state.session_info->server_info->authenticated == true)

#define	NTLM_AUTH_USERNAME(dce_call) \
(dce_call->conn->auth_state.session_info->credentials->username)

#define	NTLM_AUTH_SESSION_INFO(dce_call) \
(dce_call->conn->auth_state.session_info)

#define	NTLM_AUTH_IS_OK_RETURN(dce_call) do { \
	if (!NTLM_AUTH_IS_OK(dce_call)) {\
		return true;\
	}\
} while (0)

#define LAST_INT_FROM_BINARY(bin, size, pi) \
        if ((bin) != NULL) { \
                uint32_t        counter = 1; \
\
                *(pi) = 0; \
                do { \
                        *(pi) |= (bin)[(size) - counter]; \
                        *(pi) <<= (8 * (sizeof(uint32_t) - counter)); \
                } while (++counter < sizeof(uint32_t)); \
        }

#define FIRST_INT_FROM_BINARY(bin, pi) \
        if ((bin) != NULL) { \
                uint32_t        counter = 1; \
\
                *(pi) = 0; \
                do { \
                        *(pi) |= (bin)[sizeof(uint32_t) - counter]; \
                        *(pi) <<= (8 * (sizeof(uint32_t) - counter)); \
                } while (++counter < sizeof(uint32_t)); \
        }

#undef _PRINTF_ATTRIBUTE
#define _PRINTF_ATTRIBUTE(a1, a2) PRINTF_ATTRIBUTE(a1, a2)
/* This file was automatically generated by mkproto.pl. DO NOT EDIT */

#ifndef _PUBLIC_
#define _PUBLIC_
#endif

/* init functions definitions from gen_ndr/ndr_exchange_s.c */

NTSTATUS dcerpc_server_exchange_store_admin3_init(void);
NTSTATUS dcerpc_server_exchange_store_admin2_init(void);
NTSTATUS dcerpc_server_exchange_store_admin1_init(void);
NTSTATUS dcerpc_server_exchange_ds_rfr_init(void);
NTSTATUS dcerpc_server_exchange_sysatt_cluster_init(void);
NTSTATUS dcerpc_server_exchange_system_attendant_init(void);
NTSTATUS dcerpc_server_exchange_mta_init(void);
NTSTATUS dcerpc_server_exchange_drs_init(void);
NTSTATUS dcerpc_server_exchange_xds_init(void);
NTSTATUS dcerpc_server_exchange_mta_qadmin_init(void);
NTSTATUS dcerpc_server_exchange_store_information_init(void);
NTSTATUS dcerpc_server_exchange_nsp_init(void);
NTSTATUS dcerpc_server_exchange_emsmdb_init(void);
NTSTATUS dcerpc_server_exchange_unknown_init(void);


/* The following definitions come from server/dcesrv_exchange.c  */

void dcesrv_ec_store_admin3_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ec_store_admin3_dummy *r);
void dcesrv_ec_store_admin2_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ec_store_admin2_dummy *r);
void dcesrv_ec_store_admin1_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ec_store_admin1_dummy *r);
void dcesrv_RfrGetNewDSA(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct RfrGetNewDSA *r);
void dcesrv_RfrGetFQDNFromLegacyDN(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct RfrGetFQDNFromLegacyDN *r);
void dcesrv_sysatt_cluster_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct sysatt_cluster_dummy *r);
void dcesrv_sysatt_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct sysatt_dummy *r);
void dcesrv_MtaBind(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct MtaBind *r);
void dcesrv_MtaBindAck(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct MtaBindAck *r);
void dcesrv_ds_abandon(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_abandon *r);
void dcesrv_ds_add_entry(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_add_entry *r);
void dcesrv_ds_bind(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_bind *r);
void dcesrv_ds_compare(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_compare *r);
void dcesrv_ds_list(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_list *r);
void dcesrv_ds_modify_entry(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_modify_entry *r);
void dcesrv_ds_modify_rdn(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_modify_rdn *r);
void dcesrv_ds_read(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_read *r);
void dcesrv_ds_receive_result(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_receive_result *r);
void dcesrv_ds_remove_entry(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_remove_entry *r);
void dcesrv_ds_search(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_search *r);
void dcesrv_ds_unbind(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_unbind *r);
void dcesrv_ds_wait(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct ds_wait *r);
void dcesrv_dra_replica_add(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_replica_add *r);
void dcesrv_dra_replica_delete(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_replica_delete *r);
void dcesrv_dra_replica_synchronize(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_replica_synchronize *r);
void dcesrv_dra_reference_update(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_reference_update *r);
void dcesrv_dra_authorize_replica(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_authorize_replica *r);
void dcesrv_dra_unauthorize_replica(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_unauthorize_replica *r);
void dcesrv_dra_adopt(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_adopt *r);
void dcesrv_dra_set_status(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_set_status *r);
void dcesrv_dra_modify_entry(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_modify_entry *r);
void dcesrv_dra_delete_subref(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct dra_delete_subref *r);
void dcesrv_xds_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct xds_dummy *r);
void dcesrv_exchange_mta_qadmin(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct exchange_mta_qadmin *r);
void dcesrv_exchange_store_information_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct exchange_store_information_dummy *r);
void dcesrv_NspiSeekEntries(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiSeekEntries *r);
void dcesrv_NspiResortRestriction(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiResortRestriction *r);
void dcesrv_NspiGetPropList(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiGetPropList *r);
void dcesrv_NspiCompareDNTs(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiCompareDNTs *r);
void dcesrv_NspiModProps(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiModProps *r);
enum MAPISTATUS dcesrv_NspiGetTemplateInfo(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx, struct NspiGetTemplateInfo *r);
void dcesrv_NspiModLInkAtt(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiModLInkAtt *r);
void dcesrv_NspiDeleteEntries(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiDeleteEntries *r);
void dcesrv_NspiQueryColumns(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiQueryColumns *r);
void dcesrv_NspiGetNamesFromIDs(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiGetNamesFromIDs *r);
void dcesrv_NspiGetIDsFromNames(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct NspiGetIDsFromNames *r);
void dcesrv_EcGetMoreRpc(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct EcGetMoreRpc *r);
void dcesrv_EcDummyRpc(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct EcDummyRpc *r);
void dcesrv_EcRGetDCName(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct EcRGetDCName *r);
void dcesrv_EcRNetGetDCName(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct EcRNetGetDCName *r);
void dcesrv_EcDoRpcExt(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct EcDoRpcExt *r);
void dcesrv_unknown_dummy(struct dcesrv_call_state *dce_call, TALLOC_CTX *mem_ctx,
		       struct unknown_dummy *r);
NTSTATUS init_module(void);
#undef _PRINTF_ATTRIBUTE
#define _PRINTF_ATTRIBUTE(a1, a2)


#endif /* !_DCESRV_EXCHANGE_H_ */

