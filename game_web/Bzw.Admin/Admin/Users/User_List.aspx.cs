using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Bzw.Data;
using BCST.Common;
using IpHandle;
using Utility;

public partial class Admin_Users_User_List : AdminBasePage
{
	public int Userids = 0;
	public string UserListTitle;
	string action, action1, action2;
	string Sqlwhere = "", SqlUserCount = "";
	string UserListTypesID;
	string UserID;
	string para = "";
	int searchtop = 0;
	string sqladd = "";
    //string sqlp = "TUsers.UserID,TUsers.UserName,TUsers.Sex,TUsers.NickName,Web_Users.RegisterTM,TUserInfo.WalletMoney,TUserInfo.BankMoney,TUserInfo.Fascination,TUserInfo.Viptime,TUsers.Disabled,TUserInfo.AllLoginTime,TUsers.RegisterMac,";
     public string VipTimes, VipTimess, Sex;
	protected string order = "RegisterTM desc";

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "04" );
        //批量删除
        BatchDelete();
        //批量禁用
        BatchDisabled();
        //批量启用
        BatchEnabled();
		if( !IsPostBack )
		{
           
			UserListInfo();
		}
	}

	protected void UserListInfo()
	{		
		action = Request["act"]; //高级搜索
		action1 = Request.QueryString["act1"];   //IP搜索
		action2 = Request.QueryString["act2"];    //登录ip搜索
     
		string userType = CommonManager.Web.Request( "usertype", "" );
		string sortField = CommonManager.Web.Request( "sortfield", "" );
		string sortType = CommonManager.Web.Request( "sorttype", "" );


		//排列方式
		switch( sortField )
		{
			case "id":
				sortField = "UserID";
				break;
			case "money":
				sortField = "SumMoney";
				break;
            case "vip": sortField = "VIPTime"; break;
            case "loginc": sortField = "AllLoginTime"; break;
			default:
				sortField = "RegisterTM";
				break;
		}
		if( string.IsNullOrEmpty( sortType ) )
		{
			sortType = "desc";
		}
		order = sortField + " " + sortType;

		if( action == "post" )
		{
            
			#region 高级搜索;
			para += "act=post";
			string record = "", nickname = "", nicknameR = "", username = "", usernameR = "", grade = "", phone = "", logins = "",userid="";
			string loginR = "", reg = "", regR = "", money = "", moneyR = "", score = "", scoreR = "";
			string zz = "", zr = "", tt = "", tr = "", ii = "";

			record = Request.QueryString["d"];
			nickname = Request.QueryString["n"];
			nicknameR = Request.QueryString["nr"];
			username = Request.QueryString["u"];
			usernameR = Request.QueryString["ur"];
			userid=Request.QueryString["id"];
			grade = Request.QueryString["g"];
			phone = Request.QueryString["e"];

			logins = Request.QueryString["l"];
			loginR = Request.QueryString["lr"];
			reg = Request.QueryString["r"];
			regR = Request.QueryString["rr"];
			money = Request.QueryString["m"];
			moneyR = Request.QueryString["mr"];

			score = Request.QueryString["s"];
			scoreR = Request.QueryString["sr"];
			zz = Request.QueryString["z"];
			zr = Request.QueryString["zr"];
			tt = Request.QueryString["t"];
			tr = Request.QueryString["tr"];
			ii = Request.QueryString["i"];
			
			if( nicknameR == null )
				nicknameR = "0";
			if( usernameR == null )
				usernameR = "0";


			//判断最多显示记录数
			/*if( record != "" )
			{//Limit.outMsgBox( "最多显示记录数的值无效，必须为有效的数字!", true );
				if( !CommonManager.String.IsInteger( record ) )				
				{
					CommonManager.Web.RegJs(this, "alert('最多显示记录数的值无效，必须为有效的数字!');history.back();", false);
					return;
				}
				else
					searchtop = Convert.ToInt32( record );
				para += "&d=" + record;
			}*/

			//判断用户昵称
			if( nickname != "" )
			{
				if( Convert.ToInt32( nicknameR ) == 1 )
					sqladd = sqladd + " and nickname='" + nickname + "' ";
				else
					sqladd = sqladd + " and nickname like '%" + nickname + "%' ";
				para += "&n=" + Server.UrlEncode( nickname ) + "&nr=" + nicknameR;
			}

			//判断用户名
			if( username != "" )
			{
				if( Convert.ToInt32( usernameR ) == 1 )
					sqladd = sqladd + " and username='" + username + "' ";
				else
					sqladd = sqladd + " and username like '%" + username + "%' ";
				para += "&u=" + Server.UrlEncode( username ) + "&ur=" + usernameR;
			}

			//判断用户等级
			//if(string.IsNullOrEmpty(grade))
			//{
			//    if (Convert.ToInt32(grade) < 100)
			//    {
			//        //if (Convert.ToInt32(grade) == 5) sqladd = sqladd + " and member>=5 ";
			//        //else 
			//        sqladd = sqladd + " and TUserInfo.member=" + grade + "";
			//        para += "&g=" + grade;
			//    }
			//}

			//判断ID
			if(userid!="")
			{
				if( !CommonManager.String.IsInteger( userid ) )
				{
					CommonManager.Web.RegJs( this, "alert('用户ID只能为数字!');history.back();", false );
					return;
				}
				sqladd = sqladd + " and UserID='"+userid+"'";
			}

			//判断电话
			if( phone != "" )
			{
				sqladd = sqladd + " and Phone like '%" + phone + "%' ";
				para += "&e=" + Server.UrlEncode( phone );
			}

			//判断登录次数
			if( logins != "" )
			{
				if( !CommonManager.String.IsInteger( logins ) )
				{
					CommonManager.Web.RegJs( this, "alert('登录次数只能为数字!');history.back();", false );
					return;
				}
				if( Convert.ToInt32( loginR ) == 1 )
					sqladd = sqladd + " and allLoginTime>=" + logins + "";
				else
					sqladd = sqladd + " and allLoginTime<=" + logins + "";

				para += "&l=" + logins + "&lr=" + loginR;
			}

			//判断注册天数
			if( reg != "" )
			{
				if( !CommonManager.String.IsInteger( reg ) )
				{
					CommonManager.Web.RegJs(this, "alert('注册天数只能为数字!');history.back();", false);
					return;
				}
				if( Convert.ToInt32( regR ) == 1 )
					sqladd = sqladd + " and datediff(day, RegisterTM,getdate())>=" + reg + "";
				else
					sqladd = sqladd + " and datediff(day,RegisterTM,getdate())<=" + reg + "";
				para += "&r=" + reg + "&rr=" + regR;
			}
            Int64 mo;
			//判断用户金币数
			if( money != "" )
			{
				if( !  Int64.TryParse(money,out mo) )
				{
					CommonManager.Web.RegJs(this, "alert('用户金币数只能为数字!');history.back();", false);
					return;
				}
				if( Convert.ToInt32( moneyR ) == 1 )
					sqladd = sqladd + " and (convert(bigint,WalletMoney)+convert(bigint,BankMoney))>=" + money + "";
				else
					sqladd = sqladd + " and (convert(bigint,WalletMoney)+convert(bigint,BankMoney))<=" + money + "";
				para += "&m=" + money + "&mr=" + moneyR;
			}

			////判断用户积分数
			//if (score != "")
			//{
			//    if (!Limit.IsNumber(score)) Limit.outMsgBox("温馨提示：\\n\\n 用户积分数只能为数字!", true);
			//    if (Convert.ToInt32(scoreR) == 1) sqladd = sqladd + " and fen>=" + score + "";
			//    else sqladd = sqladd + " and fen<=" + score + "";
			//    para += "&s=" + score + "&sr=" + scoreR;
			//}

			//判断用户最后登录天数
			if( zz != "" )
			{
				if( !CommonManager.String.IsInteger( zz ) )
				{
					CommonManager.Web.RegJs(this, "alert('用户最后登录天数只能为数字!');history.back();", false);
					return;
				}
				if( Convert.ToInt32( zr ) == 1 )
					sqladd = sqladd + " and datediff(day,LastLoginTM,getdate())>=" + zz + "";
				else
					sqladd = sqladd + " and datediff(day,LastLoginTM,getdate())<=" + zz + "";
				para += "&z=" + zz + "&zr=" + zr;
			}

			//判断用户交税总数
			if( tt != "" )
			{
				if( !CommonManager.String.IsInteger( tt ) )
				{
					CommonManager.Web.RegJs(this, "alert('用户交税总数只能为数字!');history.back();", false);
					return;
				}

				if( Convert.ToInt32( tr ) == 1 )
				{
					//sqladd = sqladd + " and taxCom>=" + tt + "";
					sqladd = sqladd + "and (select sum(ChangeTax) from TChangeRecordUser as a where a.userid=Web_VUsersList.UserID)>=" + tt + "";
				}
				else
				{
					//sqladd = sqladd + " and taxCom<=" + tt + "";
					sqladd = sqladd + "and (select sum(ChangeTax) from TChangeRecordUser as a where a.userid=Web_VUsersList.UserID)<=" + tt + "";
				}
				para += "&t=" + tt;
			}

			// 限制登录大厅
			if( ii != null && ii.ToString().Length > 0 )
				sqladd = sqladd + " and Disabled=" + ii;
			if( sqladd != "" )
			{
				Sqlwhere = "and userid>=0 " + sqladd;
				SqlUserCount = Sqlwhere;
				//Response.Write(Sqlwhere + "<br><br>");
				//Response.End();
			}
			#endregion
		}
		else if( action1 == "post1" )
		{
			#region IP搜索
			//para += "act1=post1";
			string beginTime, EndTime, IPS, DayCount;
			beginTime = Request.QueryString["bt"];
			EndTime = Request.QueryString["et"];
			EndTime += DateTime.Now.ToString( " HH:mm:ss" ); //结束时间为当前时间，如"2009-04-24 17:25:30"
			IPS = CommonManager.Web.RequestUrlDecode( "IP", "" ); //Limit.editCharacter(Request.QueryString["IP"]);
         
			DayCount = Request.QueryString["dc"];

			if( DayCount == null || DayCount.ToString() == "" )
				DayCount = "0";

			if( DayCount == "1" )
			{
				Response.Redirect( "CountIp.aspx?tt=" + beginTime + "&nn=" + EndTime + "&dd=" + DayCount + "&ip=" + IPS );

			}
			else
			{
				sqladd = sqladd + "and  Convert(datetime,RegisterTM)>='" + beginTime + "' and  Convert(datetime,RegisterTM)<='" + EndTime+"'";
                if (!string.IsNullOrEmpty(IPS))
                {
                    sqladd = sqladd  +" and RegisterIP='" + IPS+"'";
                }
              
				Sqlwhere = sqladd;
				SqlUserCount = sqladd;
              
				para = "act1=post1&bt=" + beginTime + "&et=" + EndTime + "&dc=" + DayCount + "&IP=" + IPS ;

			}
			#endregion
		}

		else if( action2 == "post2" )
		{
             
			#region 登录IP搜索
			string begintime, endtime, ip;
			begintime = Request.QueryString["bt"];
			endtime = Request.QueryString["et"];
			endtime += DateTime.Now.ToString( " HH:mm:ss" ); //结束时间为当前时间，如"2009-04-24 17:25:30"
			ip = CommonManager.Web.RequestUrlDecode( "ip", "" );//Limit.editCharacter(Request.QueryString["ip"]);
			sqladd = sqladd + "and Convert(datetime,LastLoginTM)>='" + begintime + "' and Convert(datetime,LastLoginTM)<='" + endtime + "' and lastLoginIp='" + ip + "'";
			Sqlwhere = sqladd;
         

			SqlUserCount = sqladd;
			para = "act2=post2&bt=" + begintime + "&et=" + endtime + "&IP=" + ip + "";
			#endregion

		}else if(!string.IsNullOrEmpty(Request.QueryString["userid"]))
		{
             
			UserID = Request.QueryString["userid"];
			Sqlwhere =Sqlwhere+"and userid="+UserID;
		}
		else
		{
          
			#region 分类显示
			//UserListTypesID = Limit.getFormValue( "id" );
			UserListTypesID = Request.QueryString["id"];
			if( UserListTypesID != null && UserListTypesID.ToString() == "1" )      //1 ==  今日注册用户
			{
				Sqlwhere = "and datediff(day,RegisterTM,getdate())=0 ";
				SqlUserCount = "and datediff(day,RegisterTM,getdate())=0 ";
				UserListTitle = "今日注册用户";
				para = "id=" + UserListTypesID + "";
			}
			else if( UserListTypesID != null && UserListTypesID.ToString() == "2" )  //2 == 24小时注册用户
			{
				Sqlwhere = "and datediff(hour,RegisterTM,getdate())<=24 ";
				SqlUserCount = "and datediff(hour,RegisterTM,getdate())<=24 ";
				UserListTitle = "24小时注册用户";
				para = "id=" + UserListTypesID + "";
			}
			else if( UserListTypesID != null && UserListTypesID.ToString() == "3" ) //3 == 24小时登录用户
			{
				Sqlwhere = "and datediff(hour,LastLoginTM,getdate())<=24 ";
				SqlUserCount = "and datediff(hour,LastLoginTM,getdate())<=24 ";
				UserListTitle = "24小时登录用户";
				para = "id=" + UserListTypesID + "";
			}
			else
			{
				Sqlwhere = "";
				SqlUserCount = "";
				UserListTitle = "所有用户列表";
				para = "";
			}

			#endregion
		}
		//用户类型
		if( userType == "all" )
		{
            SqlUserCount = "";
            UserListTitle = "所有玩家列表";
            para = "";
		}
        else if (userType == "robotplayer")
        {
            Sqlwhere += "and IsRobot=1";
            SqlUserCount = "";
            UserListTitle = "机器人列表";
            para = "";
        }
        else
        {
            
                Sqlwhere += "and IsRobot=0";
                SqlUserCount = "";
                UserListTitle = "真实玩家列表";

          
          
        }
        


		DataTable sd = new DataTable();
       
		string[] sql = new string[2];
		string topSQL = "";
		if( searchtop > 0 )
			topSQL = " top " + searchtop;
      
		DataSet ds = DbSession.Default.FromProc( "Web_pGetDataPager" )
		   .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
		   .AddInputParameter( "@CurrentPage", DbType.Int32, PageIndex )
		   .AddInputParameter( "@Columns", DbType.String, "*" )
		   .AddInputParameter( "@TableName", DbType.String, "Web_VUsersList" )
		   .AddInputParameter( "@Wheres", DbType.String, " " + Sqlwhere )
		   .AddInputParameter( "@KeyName", DbType.String, "UserID" )
		   .AddInputParameter( "@OrderBy", DbType.String, order )
		   .ToDataSet();
		if( ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0 )
		{
			anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
			anpPageIndex.CurrentPageIndex = PageIndex;

			UserList.DataSource = ds.Tables[1];
			UserList.DataBind();
			UserList.Visible = true;
			NoUserList.Visible = false;
		}
		else
		{
			this.NoUserList.Visible = true;
			UserList.Visible = false;
		}
	}

	/// <summary>
	/// 得到用户总游戏时长
	/// </summary>
	/// <param name="userid"></param>
	/// <returns></returns>
	public string getSumPlayTimeCount( string userid )
	{
		//return new RegSql().getSumPlayTimeCount( userid );

		return new BLL.Member().GetAllPlayTimeByUserID( userid );
	}

	/// <summary>
	/// 秒转换为天、小时、分、秒
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	public string converTimer( string v )
	{
		int totalSeconds = Convert.ToInt32( v );
		int day = totalSeconds / ( 24 * 3600 );
		int hour = ( totalSeconds % ( 24 * 3600 ) ) / 3600;
		int minute = totalSeconds % 3600 / 60;
		int second = totalSeconds % 60;
		v = Convert.ToString( day + "天" + hour + "小时" + minute + "分" + second + "秒" );
		return v;
	}

	public string GetUserVip( string Userid )
	{
		DataTable table = new DataTable();
		string str = "";
		if( !( Userid != "" ) )
		{
			return "系统异常";
		}
		string strSQL = "select Member from [TUserInfo] where Userid='" + Userid + "'";
		table = DbSession.Default.FromSql( strSQL ).ToDataTable(); //this.sqlconn.sqlReader( strSQL );
		if( table.Rows.Count > 0 )
		{
			switch( Convert.ToInt32( table.Rows[0]["Member"] ) )
			{
				case 0:
					str = "一般玩家";
					break;

				case 1:
					str = "普通用户";
					break;

				case 2:
					str = "高级会员";
					break;

				case 3:
					str = "特邀嘉宾";
					break;

				case 4:
					str = "永久会员";
					break;

				case 5:
					str = "元老玩家";
					break;
			}
		}
		else
		{
			str = "用户配置异常";
		}
		table.Clear();
		return str;
	}

	public string IsVIP( string Userid )
	{
		string sql = "select DATEADD([second],TUserInfo.viptime,'1970-01-01 08:00:00') AS VipTimes from TUserInfo where userid = " + Userid + "";
		DataTable sd = new DataTable();
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader( sql );
		VipTimes = sd.Rows[0]["VipTimes"].ToString();
		if( VipTimes != "0" )
		{
			DateTime dt1 = Convert.ToDateTime( VipTimes );
			DateTime dt2 = DateTime.Now;
			if( dt2 > dt1 )
			{
				return "暂无";
			}
			else
				return Convert.ToDateTime( VipTimes ).ToString( "yyyy-MM-dd" );
		}
		else
		{
			return "暂无";
		}
	}

	public string Man( string Userid )
	{
		string sql = "select Sex from TUsers where userid = " + Userid + "";
		DataTable sd = new DataTable();
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader( sql );
		if( sd.Rows[0]["Sex"].ToString() == "1" )
		{
			return "男";
		}
		else
			return "女";
	}

	public string GetAddressByIP( string ip )
	{
		string ipfilePath =Server.MapPath( ConfigurationManager.AppSettings["IPDataUrl"]);
		IPSearch ipSearch = new IPSearch( ipfilePath );
		IPSearch.IPLocation loc = ipSearch.GetIPLocation( ip );
		return loc.country+loc.area;
	}
    //批量删除
    public void BatchDelete()
    {

        string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "batchdel")// && CommonManager.String.IsInteger(id)) //id="1,2,3,4"
        {
      
            
            //批量删除
            new BLL.Member().BatchDelete(id);
          
            string descript = "删除游戏用户ID为" + id + "的资料";
            string system = Common.GetOS;
            //管理员操作日志
            new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1);

            Response.Write("<script>alert('温馨提示：\\n\\n批量删除操作成功！');location.href='" + Request.Url.ToString().Substring(0, Request.Url.ToString().IndexOf("batchaction")) + "'; </script>");
        }
    }
    //批量禁用
    public void BatchDisabled()
    { 
         string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "batchdisabled")
        {
            
            //批量禁用
            DbSession.Default.FromSql("update Tusers set disabled=1 where userid in (" + id + ")").Execute();
            string descript = "禁用游戏用户，用户ID为" + id + "";
            string system = Common.GetOS;
            //管理员操作日志
            new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1);

            Response.Write("<script>alert('温馨提示：\\n\\n批量禁用操作成功！');location.href='" + Request.Url.ToString().Substring(0, Request.Url.ToString().IndexOf("batchaction")) + "'; </script>");

        }
    }

    //批量启用
    public void BatchEnabled()
    {
        string act = Utility.Common.GetStringOfUrl("batchaction");
        string id = Utility.Common.GetStringOfUrl("uid");
        if (act.ToLower() == "batcheabled")
        {

            //批量禁用
            DbSession.Default.FromSql("update Tusers set disabled=0 where userid in (" + id + ")").Execute();
            string descript = "启用游戏用户，用户ID为" + id + "";
            string system = Common.GetOS;
            //管理员操作日志
            new BLL.Member().InsertAdminModifyLog(AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1);

            Response.Write("<script>alert('温馨提示：\\n\\n批量启用操作成功！');location.href='" + Request.Url.ToString().Substring(0, Request.Url.ToString().IndexOf("batchaction")) + "'; </script>");

        }
    }
}
