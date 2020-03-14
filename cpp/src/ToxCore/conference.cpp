#include "ToxCore.h"

using namespace core;


/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxGroupNew
 * Signature: (I[B[B)I
 */
TOX_METHOD (jint, GroupNew,
  jint instanceNumber)
{
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_new
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxGroupChatId
 * Signature: (I[B[B)I
 */
TOX_METHOD (jbyteArray, GroupChatId,
  jint instanceNumber, jint conferenceNumber)
{
  uint8_t conference_id[TOX_CONFERENCE_ID_SIZE];
  return instances.with_instance_err (env, instanceNumber,
    [&] (bool)
      {
        return toJavaArray (env, conference_id);
      },
    tox_conference_get_id, conferenceNumber, conference_id
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxGroupInvite
 * Signature: (I[B[B)I
 */
TOX_METHOD (void, GroupInvite,
  jint instanceNumber, jint friendNumber, jint conferenceNumber)
{
  return instances.with_instance_ign (env, instanceNumber,
    tox_conference_invite, friendNumber, conferenceNumber
  );
}

TOX_METHOD (jint, GroupNumber,
  jint instanceNumber, jbyteArray conferenceId)
{
  auto conference_id = fromJavaArray (env, conferenceId);
  tox4j_assert (!conferenceId || conference_id.size () == TOX_CONFERENCE_ID_SIZE);
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_by_id, conference_id
  );
}