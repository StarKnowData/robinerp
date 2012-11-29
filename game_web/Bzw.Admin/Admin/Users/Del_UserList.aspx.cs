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
using Utility;
using BCST.Common;
using Bzw.Data;
public partial class Admin_Users_Dle_UserList : AdminBasePage
{
    int userlistid;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");

		//if (!Limit.IsNumeric(Limit.editCharacter(Limit.getFormValue("id"))))
		//    Limit.outMsgBox("温馨提示：\\n\\n参数传递错误！", true);
		//else
		//    userlistid = Convert.ToInt32(Limit.getFormValue("id"));
		string uid = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( uid ) || !CommonManager.String.IsInteger( uid ) )
		{
			CommonManager.Web.RegJs(this,"alert('参数错误！');",false);
			return;
		}
		userlistid = int.Parse( uid );

		//sql = "delete from [Tusers] Where userID='" + userlistid + "'";
		//sqlconn.sqlReader(sql);

		DbSession.Default.FromSql( "delete from [Tusers] Where UserID=@UserID" ).AddInputParameter( "@UserID", DbType.Int32, uid ).Execute();

		string descript = "删除游戏用户ID为" + uid + "的资料";
        string system = Common.GetOS;

		new BLL.Member().InsertAdminModifyLog( AdminInfo["UserName"].ToString(), Common.RequestIP, system, descript, 1 );
        //Limit.outMsgBox("温馨提示：\\n\\n操作成功！", "User_List.aspx",true);
		Response.Write( "<script>alert('温馨提示：\\n\\n删除操作成功！');location.href='"+Server.UrlDecode( Utility.Common.GetStringOfUrl("url"))+"';</script>" );
    }
}
