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

public partial class Admin_Games_GameNamesDel : AdminBasePage
{
    string nameids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');", false );
			return;
		}
		else
			nameids = tmp; //Limit.editCharacter(Limit.getFormValue("id"));
        //删除客户端和服务端的游戏信息
        string sql = "delete from TGameNameInfo where NameID=" + nameids + ";delete from TGameServerInfo where NameID=" + nameids;
		//sqlconn.sqlReader(sql);
		//Limit.outMsgBox("温馨提示：\\n\\n删除操作成功！","GameNames.aspx", true);
		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('删除操作成功！');location.href='GameNames.aspx';</script>");
    }
}
