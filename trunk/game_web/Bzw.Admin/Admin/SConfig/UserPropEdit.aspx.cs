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
using BCST.Common;
using Bzw.Data;
using System.Text;
using System.Text.RegularExpressions;

public partial class Admin_SConfig_UserPropEdit : AdminBasePage
{
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "15" );

		if( string.IsNullOrEmpty( ParamsUrlDecode ) )
		{
			CommonManager.Web.RegJs( this, "history.back();", false );
			return;
		}

		ltUserName.Text = ParamsUrlDecode;

		if( IsPostBack )
			return;

		//1、读取玩家道具表
		string sql = @"select up.*,tu.UserName,pd.PropName from tuserprop as up
						inner join TPropDefine as pd
						on up.PropID=pd.PropID
						inner join TUsers as tu
						on up.UserID=tu.UserID
						where tu.UserName=@UserName
						order by UserID desc,PropID asc
						";
		DataTable dt = DbSession.Default.FromSql( sql ).AddInputParameter( "@UserName", DbType.String, ParamsUrlDecode ).ToDataTable();
		if( dt.Rows.Count <= 0 )
		{
			Literal lt = new Literal();
			lt.Text = "该用户还没有购买过道具。";
			phPropList.Controls.Add( lt );
			return;
		}
		//2、构造动态表单
		foreach( DataRow row in dt.Rows )
		{
			HtmlTableRow tr = new HtmlTableRow();

			HtmlTableCell th = new HtmlTableCell( "TH" );
			th.Align = "right";
			th.InnerText = row["PropName"].ToString() + "：";
			tr.Controls.Add( th );

			HtmlTableCell td = new HtmlTableCell();
			td.Align = "left";

			HtmlInputText txt = new HtmlInputText();
			txt.Attributes.Add("maxlength", "7");
			txt.Attributes.Add( "class", "put" );
			txt.Attributes.Add( "style", "ime-mode:disabled;" );
			txt.Attributes.Add( "onkeypress", "return KeyPressNum(this,event);" );
			txt.Value = row["HoldCount"].ToString();
			txt.ID = "txt_" + row["UserID"].ToString() + "_" + row["PropID"].ToString();

			td.Controls.Add( txt );
			tr.Controls.Add( td );

			phPropList.Controls.Add( tr );
		}
	}

	protected void btnSubmit_Click( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;

		//查询所有道具id
		DataTable propdt = DbSession.Default.FromSql( "select PropID from TPropDefine" ).ToDataTable();
		//先查询当前道具记录
		string sql = @"select up.*,tu.UserName,pd.PropName from tuserprop as up
						inner join TPropDefine as pd
						on up.PropID=pd.PropID
						inner join TUsers as tu
						on up.UserID=tu.UserID
						where tu.UserName=@UserName
						order by UserID desc,PropID asc
						";
		DataTable dt = DbSession.Default.FromSql( sql ).AddInputParameter( "@UserName", DbType.String, ParamsUrlDecode ).ToDataTable();
		//构造更新语句
		sql = "update TUserProp set HoldCount={0} where UserID={1} and PropID={2};";
		string insert = "insert into Web_PropChangeLog (ActionDate,AdminName,UserID,PropID,BeforeNum,AfterNum) values (getdate(),'{0}',{1},{2},{3},{4});";
		StringBuilder commond = new StringBuilder();
		//循环拼凑更新语句
		foreach( string key in Request.Form.AllKeys )
		{
			if( !key.StartsWith( "txt_" ) )
				continue;
			//从key中得到道具id
			Match m = Regex.Match( key, @"txt_(\d+)_(\d+)", RegexOptions.IgnoreCase | RegexOptions.Singleline );
			if( !m.Success )
				continue;
			string uid = m.Groups[1].Value;//用户id
			string pid = m.Groups[2].Value;//道具id
			//如果不存在此id的道具则返回
			if( string.IsNullOrEmpty( pid ) || !CommonManager.String.IsInteger( pid ) || ( propdt.Select( "PropID=" + pid ).Length <= 0 ) )
				continue;
			//验证值的输入
			string value = CommonManager.Web.RequestForm( key, "" );
			if( string.IsNullOrEmpty( value ) || !CommonManager.String.IsInteger( value ) || int.Parse( value ) <= 0 )
			{
				CommonManager.Web.RegJs( this, "alert('请正确输入道具数量。');LocationToMe();", false );
				return;
			}
			//取得更新前的值
			int old_value = (int)(dt.Select( "PropID=" + pid )[0]["HoldCount"]);
			//添加格式化更新字符串
			commond.AppendFormat( sql, value, uid, pid );
			if( int.Parse( value ) != old_value )
			{
				//如果有更改，则添加插入记录语句
				//Session["AdminName"].ToString();
				commond.AppendFormat(insert, AdminInfo["UserName"].ToString(), uid, pid, old_value, value);
			}
		}
		if (!commond.ToString().Equals(""))
		{
			//执行更新语句
			DbSession.Default.FromSql(commond.ToString()).Execute();
			CommonManager.Web.RegJs(this, "alert('修改成功！');LocationToMe();", false);
		}
		else
		{
			CommonManager.Web.RegJs(this, "LocationToMe();", false);
		}
	}
}
