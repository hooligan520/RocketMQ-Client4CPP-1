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
#if!defined __TOPICFILTERTYPE_H__
#define __TOPICFILTERTYPE_H__

/**
 * Topic过滤方式，默认为单TAG过滤
 *
 */

enum TopicFilterType
{
	/**
	* 每个消息只能有一个Tag
	*/
	SINGLE_TAG,
	/**
	* 每个消息可以有多个Tag（暂时不支持，后续视情况支持）<br>
	* 为什么暂时不支持？<br>
	* 此功能可能会对用户造成困扰，且方案并不完美，所以暂不支持
	*/
	MULTI_TAG
};

#endif
