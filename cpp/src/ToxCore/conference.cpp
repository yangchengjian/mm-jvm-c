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

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceJoin
 * Signature: (IIII[B)I
 */
TOX_METHOD (jint, ConferenceJoin,
  jint instanceNumber, jint friendNumber, jbyteArray cookie)
{
  auto cookie_array = fromJavaArray (env, cookie);

  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_join, friendNumber, cookie_array.data (), cookie_array.size ()
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceSendMessage
 * Signature: (IIII[B)I
 */
TOX_METHOD (bool, ConferenceSendMessage,
  jint instanceNumber, jint conferenceNumber, jint messageType, jint timeDelta, jbyteArray message)
{
  auto message_array = fromJavaArray (env, message);

  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_send_message, conferenceNumber, Enum::valueOf<TOX_MESSAGE_TYPE> (env, messageType), message_array.data (), message_array.size ()
  );
}