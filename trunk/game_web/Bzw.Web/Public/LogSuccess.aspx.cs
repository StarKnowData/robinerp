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
using System.Text;

using BCST.Common;
using Bzw.Data;

public partial class Public_LogSuccess : UiCommon.BasePage
{
	protected void Page_Load(object sender, EventArgs e)
	{
		StringBuilder strRetrun = new StringBuilder("");

		try
		{
			if (UiCommon.UserLoginInfo.IsLogin)
			{
				string userName = string.Empty;
				string NickName = string.Empty;
				string Money = string.Empty;
				string Wallet = string.Empty;
				string LastLoginTm = string.Empty;

				string sql = "select UserName,NickName,BankMoney,WalletMoney,LastLoginTM from TUsers,TUserinfo  Where TUsers.userid=TUserinfo.userid and TUsers.userName='" + UiCommon.UserLoginInfo.UserName + "'";
				DataTable dt = DbSession.Default.FromSql(sql).ToDataTable();
				if (dt.Rows.Count > 0)
				{
					userName = dt.Rows[0]["UserName"].ToString();
					NickName = dt.Rows[0]["NickName"].ToString();
					Money = UiCommon.StringConfig.AddZeros(dt.Rows[0]["BankMoney"]);
					Wallet = UiCommon.StringConfig.AddZeros(dt.Rows[0]["WalletMoney"]);
					LastLoginTm = ((DateTime)dt.Rows[0]["LastLoginTM"]).ToString("yyyy-MM-dd");
				}
				strRetrun.AppendFormat( "<span>您好，欢迎您：<a href=\"/Manage/\" title=\"管理中心\">{0}</a> </span> <a href=\"/Manage/\">管理中心</a> <a href=\"/Public/Logout.aspx\">退出</a>", NickName );
			}

			Response.Write(strRetrun.ToString());
		}
		catch (Exception ex)
		{
			Response.Write(strRetrun.ToString());
		}
	}
}


/*
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
using System.Text;

using com.FlySky.DBConnect;
using BCST.Common;

public partial class Public_LogSuccess : UiCommon.BasePage
{
	sqlConnection sqlconn = new sqlConnection();

	protected void Page_Load( object sender, EventArgs e )
	{
		StringBuilder strRetrun = new StringBuilder( "" );

		try
		{
			if( UiCommon.UserLoginInfo.IsLogin )
			{
				DataTable sd = new DataTable();
				string sql = "select * from TUsers,TUserinfo  Where TUsers.userid=TUserinfo.userid and TUsers.userName='" + UiCommon.UserLoginInfo.UserName + "'";
				sd =  sqlconn.sqlReader( sql );
				if( sd.Rows.Count > 0 )
				{
                    string userName = sd.Rows[0]["username"].ToString();
					string NickName = sd.Rows[0]["NickName"].ToString();
					string Money = sd.Rows[0]["BankMoney"].ToString();
					string Wallet = sd.Rows[0]["WalletMoney"].ToString();
					string LastLoginTm = sd.Rows[0]["LastLoginTM"].ToString();

					string position = CommonManager.Web.Request( "position", "" );
					if( string.IsNullOrEmpty( position ) )
					{

						#region old code
						strRetrun.Append( "<div class=\"sid_box\">" );
						strRetrun.Append( "<div class=\"s_box_t1\">" + userName + ", 欢迎您！</div>" );
						strRetrun.Append( "<div class=\"s_box_m\">" );
						strRetrun.Append( "<p class=\"p4\">银行存款：<b id=\"lgbank\">" + Money + " 金币</b><br />" );
						strRetrun.Append( "剩余金币：<b>" + Wallet + " 金币</b><br />" );
						strRetrun.Append( "最后登录：" + LastLoginTm + "<br />" );
						strRetrun.Append( "<a href=\"/Manage/Default.aspx\">个人管理中心</a> | <a href=\"/Manage/Pay/PointCard.aspx\">点卡充值</a> | <a href=\"/Public/Logout.aspx\">退出</a> </p>" );
						strRetrun.Append( "</div>" );
						strRetrun.Append( "<div class=\"s_box_b\"></div>" );
						strRetrun.Append( "</div>" );
						#endregion
					}
					else if(position == "index")
					{
						#region new code
						strRetrun.Append( "<table width=\"250\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" class=\"loginForm\">" );
						strRetrun.Append( "<tr>" );
						strRetrun.Append( "<th colspan=\"2\" style='text-align:left; padding-left:5px;width:150px;'>" );
						strRetrun.Append( userName + "，欢迎您！</th>" );

						strRetrun.Append( "</tr>" );
						strRetrun.Append( "<tr>" );
						strRetrun.Append( "<th>" );
						strRetrun.Append( "银行存款：</th>" );
						strRetrun.Append( "<td>" );
                        strRetrun.Append("<span id=\"lgbank\">" + Money + " 金币</span></td>");
						strRetrun.Append( "</tr>" );
						strRetrun.Append( "<tr>" );
						strRetrun.Append( "<th>" );
						strRetrun.Append( "剩余金币：</th>" );
						strRetrun.Append( "<td>" );
						strRetrun.Append( Wallet + " 金币</td>" );
						strRetrun.Append( "</tr>" );
						strRetrun.Append( "<tr>" );
						strRetrun.Append( "<th>" );
						strRetrun.Append( "最后登录：</th>" );
						strRetrun.Append( "<td>" );
						strRetrun.Append( LastLoginTm );
						strRetrun.Append( "</td>" );
						strRetrun.Append( "</tr>" );
						strRetrun.Append( "<tr>" );
						strRetrun.Append( "<td colspan=\"2\">" );
						strRetrun.Append( "<a href=\"/Manage/Default.aspx\">个人管理中心</a> | <a href=\"/Manage/Pay/PointCard.aspx\">点卡充值</a> | <a href=\"/Public/Logout.aspx\">退出</a>" );
						strRetrun.Append( "</td>" );
						strRetrun.Append( "</tr>" );
						strRetrun.Append( "</table>" );
						#endregion
					}
				}
			}

			Response.Write( strRetrun.ToString() );
		}
		catch( Exception ex )
		{
			//Response.Write(ex.Message + ex.Source + ex.StackTrace);
			Response.Write( strRetrun.ToString() );
		}
	}
}*/