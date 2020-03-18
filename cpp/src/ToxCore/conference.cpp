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
 * Method:    toxConferenceSetTitle
 * Signature: (I[B)V
 */
TOX_METHOD (void, ConferenceSetTitle,
  jint instanceNumber, jint conference_number, jbyteArray title)
{
  auto title_array = fromJavaArray (env, title);
  return instances.with_instance_ign (env, instanceNumber,
    tox_conference_set_title, conference_number, title_array.data (), title_array.size ());
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceGetTitleSize
 * Signature: (IIII[B)I
 */
TOX_METHOD (jint, ConferenceGetTitleSize,
  jint instanceNumber, jint conferenceNumber)
{
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_get_title_size, conferenceNumber
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferenceGetTitle
 * Signature: (II)[B
 */
TOX_METHOD (jbyteArray, ConferenceGetTitle,
  jint instanceNumber, jint conferenceNumber)
{
  uint8_t title[TOX_MAX_NAME_LENGTH];
  return instances.with_instance_err (env, instanceNumber,
    [&] (bool)
      {
        return toJavaArray (env, title);
      },
    tox_conference_get_title, conferenceNumber, title
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferencePeerGetNameSize
 * Signature: (IIII[B)I
 */
TOX_METHOD (jint, ConferencePeerGetNameSize,
  jint instanceNumber, jint conferenceNumber, jint peerNumber)
{
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_peer_get_name_size, conferenceNumber, peerNumber
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferencePeerGetName
 * Signature: (II)[B
 */
TOX_METHOD (jbyteArray, ConferencePeerGetName,
  jint instanceNumber, jint conferenceNumber, jint peerNumber)
{
  uint8_t name[TOX_MAX_NAME_LENGTH];
  return instances.with_instance_err (env, instanceNumber,
    [&] (bool)
      {
        return toJavaArray (env, name);
      },
    tox_conference_peer_get_name, conferenceNumber, peerNumber, name
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxConferencePeerCount
 * Signature: (I[B[B)I
 */
TOX_METHOD (jint, ConferencePeerCount,
  jint instanceNumber, jint conferenceNumber)
{
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_peer_count, conferenceNumber
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