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
public partial class Admin_GameInfo_GameMainDel : AdminBasePage
{
    string gameids;
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
			gameids = tmp; //Limit.editCharacter(Limit.getFormValue("id"));
        string sql = "delete  from web_GameInfo where Game_id=" + gameids + "";
		//sqlconn.sqlReader(sql);
		//Limit.outMsgBox("温馨提示：\\n\\n删除操作执行成功！","GameMain.aspx", true);
		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('删除操作成功！');location.href='GameMain.aspx';</script>" );
    }
}
