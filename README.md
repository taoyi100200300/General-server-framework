# General-server-framework
通用服务器框架
基于C++ boost，用于快速开发网络服务器程序

会话<----->服务器：

-------------------------------------1-----------------------------------

	session：处理所有服务器与客户端交互的业务流程，基于此类派生出包含业务流的会话类传递给服务器用于快速开发服务器
		派生类需实现的接口：
			virtual void on_connected()
				当连接建立时需要实现的业务流程
			virtual void on_data_recv(unsigned char* buff, std::size_t bytes_transferred)
				当接收到数据时的数据处理流程
				参数：
					buff 				接收到的数据
					bytes_transferred	接收到的数据长度
			virtual void on_data_send()
				当数据发送完毕时的后续业务流程
			virtual void on_disconnected()
				连接断开时的业务流程
	方法：
		void send_data(const unsigned char* data, size_t bytes_transferred)
			发送数据
			参数：	data				待发送数据
					bytes_transferred	待发送数据长度
					
			void close_socket()
			断开连接


------------------------------------2------------------------------------

	server：处理服务器所有session、所有消息以及线程池的服务器框架核心
	方法：
		boost::shared_ptr<T> create_session(std::string ip, unsigned short port)
		创建一个与指定ip/port相连的会话对象
		boost::shared_ptr<T> get_session_by_uid(boost::uuids::uuid uid)
		通过uid取得此服务器管理的一个session
		void delete_session(boost::uuids::uuid uid)
		通过uid删除此服务器管理的一个session
	
	

消息->动作接口：

------------------------------------1------------------------------------

	message_sender:消息发送者，任何需要向server发送消息的对象都需要由此类派生，session就派生自message_sender
		在创建此类对象时指定消息来源的类型、服务器实例并自动产生uid用于辨别消息投递者
	构造：
		message_sender(message_queue& message_loop, source_type src_type)
		参数：
			message_loop	消息队列实例
			src_type		消息源类型
	方法：
	
		void send_msg(message_type msg_type, boost::shared_ptr<void> extra_message)
		发送消息
		参数：
			msg_type		消息类型
			extra_message	附加消息
		

------------------------------------2------------------------------------

	message：服务器消息
		消息内容：
			source_type src_type					消息来源类型
			boost::uuids::uuid uid					消息发送者的uid
			message_type msg_type					消息类型
			boost::shared_ptr<void> extra_message	附加消息
		action根据消息来源类型、消息发送者的uid、消息类型判断此消息是否为自己负责处理的消息。如果是，则根据需要解析附加消息执行动作
	
	
------------------------------------3-----------------------------------

	message_queue：消息循环，服务器由此类派生，message_sender在创建时需要指定消息投递的对象


------------------------------------4-----------------------------------

	Action：处理服务器消息队列中的消息，每个消息都有对应的Action
		派生类需实现的接口：
			virtual bool action_event(boost::shared_ptr<message> msg)
				完成消息的分析处理，若在这个action中完成消息的处理则返回true，否则返回false，将消息传递给消息处理链的下一节点处理
				参数：
					boost::shared_ptr<message> msg	消息
		
		基于此类派生的动作可调用server对应的add函数添加至消息处理链
			add_on_connect_action		添加至连接建立消息链
			add_on_disconnect_action	添加至连接断开消息链
			add_on_error_action			添加至错误消息链
			add_on_user_define_action	添加至用户自定义消息链
			连接建立消息链、连接断开消息链、错误消息链中有默认的动作处理器，用户自定义消息链中没有。
			为实现服务器的稳定安全，所有对server的操作都应在action中完成，需要对server操作时可以投递消息，通知action完成对服务器的操作
		
配置文件读取接口：

	configure：服务器读取配置文件
	构造：
		configure(std::string ini_path);
		参数：	ini_path	配置文件路径
	方法：
	T get_value(std::string node_id, std::string cfg_id,T defaule_value)
		读取配置项
		参数：
			node_id			配置节点名称
			cfg_id			配置项名称
			defaule_value	配置项默认值
			
日志接口：

	void g_InitLog(std::string log_path)
	初始化日志系统
	参数：	log_path	日志存放路径
	使用时申明一个日志对象
	src::severity_channel_logger<SeverityLevel, std::string> logger;
	然后直接使用流运算符写入
	BOOST_LOG_SEV(logger, Log_Info) << "test";
	
定时器接口：

	timer：所有定时器可由此类派生，实现定时触发执行指定任务
	派生类需实现的接口：
		virtual void timer_tast()
		定时执行的任务
	方法：
		timer(int second)
		构造，并设定触发间隔
		void set_interval(int second)
		设定触发间隔
		void timer_run()
		开启定时器
		void timer_stop()
		停止定时器
