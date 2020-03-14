#include "ToxCore.h"

using namespace core;


/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceNew
 * Signature: (I[B[B)I
 */
TOX_METHOD (jint, ConferenceNew,
  jint instanceNumber)
{
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_new
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceNumber
 * Signature: (I[B[B)I
 */
TOX_METHOD (jint, ConferenceNumber,
  jint instanceNumber, jbyteArray conferenceId)
{
  auto conference_id = fromJavaArray (env, conferenceId);
  tox4j_assert (!conferenceId || conference_id.size () == TOX_CONFERENCE_ID_SIZE);
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_by_id, conference_id
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceId
 * Signature: (I[B[B)I
 */
TOX_METHOD (jbyteArray, ConferenceId,
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
 * Method:    toxConferenceInvite
 * Signature: (I[B[B)I
 */
TOX_METHOD (void, ConferenceInvite,
  jint instanceNumber, jint friendNumber, jint conferenceNumber)
{
  return instances.with_instance_ign (env, instanceNumber,
    tox_conference_invite, friendNumber, conferenceNumber
  );
}