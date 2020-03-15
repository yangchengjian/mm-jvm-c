package im.tox.tox4j.core.bench

import im.tox.tox4j.bench.TimingReport
import im.tox.tox4j.bench.ToxBenchBase._
import im.tox.tox4j.core.callbacks.ToxCoreEventAdapter
import im.tox.tox4j.core.data.{ ToxConferenceNumber, ToxFriendNumber, ToxNickname, ToxPublicKey }
import im.tox.tox4j.core.enums.{ ToxConnection, ToxFileControl, ToxMessageType, ToxUserStatus }
import im.tox.tox4j.core.{ ToxCore, ToxCoreConstants }
import im.tox.tox4j.impl.jni.ToxCoreImpl
import im.tox.tox4j.testing.GetDisjunction._

final class CoreCallbackTimingBench extends TimingReport {

  private val eventListener = new ToxCoreEventAdapter[Unit]

  private val friendNumber = ToxFriendNumber.fromInt(1).get
  private val publicKey = ToxPublicKey.fromValue(Array.ofDim[Byte](ToxCoreConstants.PublicKeySize)).toOption.get
  private val nickname = ToxNickname.fromValue(Array.ofDim[Byte](ToxNickname.MaxSize)).toOption.get
  private val data = Array.ofDim[Byte](ToxCoreConstants.MaxCustomPacketSize)
  private val conferenceNumber = ToxConferenceNumber.fromInt(1).get
  private val peerNumber = ToxPeerNumber.fromInt(1).get

  def invokePerformance(method: String, f: ToxCoreImpl => Unit): Unit = {
    performance of method in {
      usingTox(iterations1k) in {
        case (sz, tox: ToxCoreImpl) =>
          (0 until sz) foreach { _ =>
            f(tox)
            tox.iterate(eventListener)(())
          }
      }
    }
  }

  def invokeAllCallbacks(tox: ToxCoreImpl): Unit = {
    tox.invokeFileChunkRequest(friendNumber, 2, 3, 4)
    tox.invokeFileRecv(friendNumber, 2, 3, 4, data)
    tox.invokeFileRecvChunk(friendNumber, 2, 3, data)
    tox.invokeFileRecvControl(friendNumber, 2, ToxFileControl.PAUSE)
    tox.invokeFriendConnectionStatus(friendNumber, ToxConnection.TCP)
    tox.invokeFriendLosslessPacket(friendNumber, data)
    tox.invokeFriendLossyPacket(friendNumber, data)
    tox.invokeFriendMessage(friendNumber, ToxMessageType.NORMAL, 2, data)
    tox.invokeFriendName(friendNumber, nickname)
    tox.invokeFriendReadReceipt(friendNumber, 2)
    tox.invokeFriendRequest(publicKey, 1, data)
    tox.invokeFriendStatus(friendNumber, ToxUserStatus.AWAY)
    tox.invokeFriendStatusMessage(friendNumber, data)
    tox.invokeFriendTyping(friendNumber, isTyping = true)
    tox.invokeSelfConnectionStatus(ToxConnection.TCP)
    tox.invokeConferenceInvite(conferenceNumber, 1)
    tox.invokeConferenceMessage(conferenceNumber, peerNumber, ToxMessageType.NORMAL, 2, data)
  }

  timing.of[ToxCore] {

    measure method "iterate" in {
      usingTox(iterations1k) in {
        case (sz, tox) =>
          (0 until sz) foreach { _ =>
            tox.iterate(eventListener)(())
          }
      }
    }

    performance of "enqueuing a callback" in {
      usingTox(iterations1k) in {
        case (sz, tox: ToxCoreImpl) =>
          (0 until sz) foreach { _ =>
            tox.invokeFileChunkRequest(friendNumber, 2, 3, 4)
          }
      }
    }

    performance of "enqueue all callbacks" in {
      usingTox(iterations1k) in {
        case (sz, tox: ToxCoreImpl) =>
          (0 until sz) foreach { _ =>
            invokeAllCallbacks(tox)
          }
      }
    }

    performance of "call all callbacks" in {
      usingTox(iterations1k) in {
        case (sz, tox: ToxCoreImpl) =>
          (0 until sz) foreach { _ =>
            invokeAllCallbacks(tox)
            tox.iterate(eventListener)(())
          }
      }
    }

    invokePerformance("invokeFileChunkRequest", _.invokeFileChunkRequest(friendNumber, 2, 3, 4))
    invokePerformance("invokeFileRecv", _.invokeFileRecv(friendNumber, 2, 3, 4, data))
    invokePerformance("invokeFileRecvChunk", _.invokeFileRecvChunk(friendNumber, 2, 3, data))
    invokePerformance("invokeFileRecvControl", _.invokeFileRecvControl(friendNumber, 2, ToxFileControl.PAUSE))
    invokePerformance("invokeFriendConnectionStatus", _.invokeFriendConnectionStatus(friendNumber, ToxConnection.TCP))
    invokePerformance("invokeFriendLosslessPacket", _.invokeFriendLosslessPacket(friendNumber, data))
    invokePerformance("invokeFriendLossyPacket", _.invokeFriendLossyPacket(friendNumber, data))
    invokePerformance("invokeFriendMessage", _.invokeFriendMessage(friendNumber, ToxMessageType.NORMAL, 2, data))
    invokePerformance("invokeFriendName", _.invokeFriendName(friendNumber, nickname))
    invokePerformance("invokeFriendReadReceipt", _.invokeFriendReadReceipt(friendNumber, 2))
    invokePerformance("invokeFriendRequest", _.invokeFriendRequest(publicKey, 1, data))
    invokePerformance("invokeFriendStatus", _.invokeFriendStatus(friendNumber, ToxUserStatus.AWAY))
    invokePerformance("invokeFriendStatusMessage", _.invokeFriendStatusMessage(friendNumber, data))
    invokePerformance("invokeFriendTyping", _.invokeFriendTyping(friendNumber, isTyping = true))
    invokePerformance("invokeSelfConnectionStatus", _.invokeSelfConnectionStatus(ToxConnection.TCP))
    invokePerformance("invokeConferenceInvite", _.invokeConferenceInvite(conferenceNumber, 1))
    invokePerformance("invokeConferenceMessage", _.invokeConferenceMessage(conferenceNumber, peerNumber, ToxMessageType.NORMAL, 2, data))
  }

}
