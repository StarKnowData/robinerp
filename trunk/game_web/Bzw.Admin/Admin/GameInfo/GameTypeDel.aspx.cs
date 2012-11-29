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

public partial class Admin_GameInfo_GameTypeDel : AdminBasePage
{
    string typeids;
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
			typeids = tmp; //Limit.editCharacter(Limit.getFormValue("id"));
        string sql = "delete from web_GameType where Typeid=" + typeids + "";
		//sqlconn.sqlReader(sql);
		//Limit.outMsgBox("温馨提示：\\n\\n游戏分类删除成功！", "GameType.aspx", true);
		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('游戏分类删除成功！');location.href='GameType.aspx';</script>" );
    }
}
