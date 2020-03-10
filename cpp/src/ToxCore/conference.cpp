#include "ToxCore.h"

using namespace core;


/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxNewGroup
 * Signature: (I[B[B)I
 */
TOX_METHOD (jint, NewGroup,
  jint instanceNumber)
{
  return instances.with_instance_err (env, instanceNumber,
    identity,
    tox_conference_new
  );
}

/*
 * Class:     im_tox_tox4j_impl_ToxCoreJni
 * Method:    toxGetGroupChatId
 * Signature: (I[B[B)I
 */
TOX_METHOD (jbyteArray, GetGroupChatId,
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


