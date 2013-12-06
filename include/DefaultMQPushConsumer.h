/**
* Copyright (C) 2013 kangliqiang ,kangliq@163.com
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/
#if!defined __DEFAULTMQPUSHCONSUMER_H__
#define __DEFAULTMQPUSHCONSUMER_H__

#include <list>
#include <string>

#include "MQPushConsumer.h"
#include "MessageExt.h"
#include "ClientConfig.h"
#include "RocketMQClient.h"

class AllocateMessageQueueStrategy;
class DefaultMQPushConsumerImpl;
class OffsetStore;

/**
* 类似于Broker Push消息到Consumer方式，但实际仍然是Consumer内部后台从Broker Pull消息<br>
* 采用长轮询方式拉消息，实时性同push方式一致，且不会无谓的拉消息导致Broker、Consumer压力增大
*
*/
class ROCKETMQCLIENT_API DefaultMQPushConsumer : public ClientConfig ,public MQPushConsumer
{
public:
	DefaultMQPushConsumer();
	DefaultMQPushConsumer(const std::string& consumerGroup);

	//MQAdmin
	void createTopic(const std::string& key, const std::string& newTopic, int queueNum);
	long long searchOffset(const MessageQueue& mq, long long timestamp);
	long long maxOffset(const MessageQueue& mq);
	long long minOffset(const MessageQueue& mq);
	long long earliestMsgStoreTime(const MessageQueue& mq);
	MessageExt viewMessage(const std::string& msgId);
	QueryResult queryMessage(const std::string& topic,
							 const std::string&  key,
							 int maxNum,
							 long long begin,
							 long long end);

	// MQadmin end

	AllocateMessageQueueStrategy* getAllocateMessageQueueStrategy();
	void setAllocateMessageQueueStrategy(AllocateMessageQueueStrategy* pAllocateMessageQueueStrategy);
	
	int getConsumeConcurrentlyMaxSpan();
	void setConsumeConcurrentlyMaxSpan(int consumeConcurrentlyMaxSpan);

	ConsumeFromWhere getConsumeFromWhere();
	void setConsumeFromWhere(ConsumeFromWhere consumeFromWhere);

	int getConsumeMessageBatchMaxSize();
	void setConsumeMessageBatchMaxSize(int consumeMessageBatchMaxSize);

	std::string getConsumerGroup();
	void setConsumerGroup(const std::string& consumerGroup) ;

	int getConsumeThreadMax() ;
	void setConsumeThreadMax(int consumeThreadMax);

	int getConsumeThreadMin();
	void setConsumeThreadMin(int consumeThreadMin);

	MessageListener* getMessageListener();
	void setMessageListener(MessageListener* pMessageListener);

	MessageModel getMessageModel();
	void setMessageModel(MessageModel messageModel) ;

	int getPullBatchSize() ;
	void setPullBatchSize(int pullBatchSize);

	long getPullInterval();
	void setPullInterval(long pullInterval);

	int getPullThresholdForQueue();
	void setPullThresholdForQueue(int pullThresholdForQueue);

	std::map<std::string, std::string>& getSubscription();
	void setSubscription(const std::map<std::string, std::string>& subscription);

	//MQConsumer
	void sendMessageBack(MessageExt& msg, int delayLevel);
	std::set<MessageQueue>* fetchSubscribeMessageQueues(const std::string& topic);

	void start();
	void shutdown();
	//MQConsumer end
	
	//MQPushConsumer
	void registerMessageListener(MessageListener* pMessageListener);

	void subscribe(const std::string& topic, const std::string& subExpression);
	void unsubscribe(const std::string& topic);

	void updateCorePoolSize(int corePoolSize);

	void suspend() ;
	void resume();
	//MQPushConsumer end

	OffsetStore* getOffsetStore();
	void setOffsetStore(OffsetStore* offsetStore);

	DefaultMQPushConsumerImpl* getDefaultMQPushConsumerImpl();

protected:
	DefaultMQPushConsumerImpl* m_pDefaultMQPushConsumerImpl;

private:
	/**
	* 做同样事情的Consumer归为同一个Group，应用必须设置，并保证命名唯一
	*/
	std::string m_consumerGroup;

	/**
	* 集群消费/广播消费
	*/
	MessageModel m_messageModel;

	/**
	* Consumer启动时，从哪里开始消费
	*/
	ConsumeFromWhere m_consumeFromWhere;

	/**
	* 队列分配算法，应用可重写
	*/
	AllocateMessageQueueStrategy* m_pAllocateMessageQueueStrategy ;

	/**
	* 订阅关系
	*/
	std::map<std::string /* topic */, std::string /* sub expression */> m_subscription ;

	/**
	* 消息监听器
	*/
	MessageListener* m_pMessageListener;

	/**
	* Offset存储，系统会根据客户端配置自动创建相应的实现，如果应用配置了，则以应用配置的为主
	*/
	OffsetStore* m_pOffsetStore;

	/**
	* 消费消息线程，最小数目
	*/
	int m_consumeThreadMin;

	/**
	* 消费消息线程，最大数目
	*/
	int m_consumeThreadMax;

	/**
	* 同一队列并行消费的最大跨度，顺序消费方式情况下，此参数无效
	*/
	int m_consumeConcurrentlyMaxSpan;

	/**
	* 本地队列消息数超过此阀值，开始流控
	*/
	int m_pullThresholdForQueue;

	/**
	* 拉消息间隔，如果为了降低拉取速度，可以设置大于0的值
	*/
	long m_pullInterval;

	/**
	* 消费一批消息，最大数
	*/
	int m_consumeMessageBatchMaxSize;

	/**
	* 拉消息，一次拉多少条
	*/
	int m_pullBatchSize;
};

#endif
