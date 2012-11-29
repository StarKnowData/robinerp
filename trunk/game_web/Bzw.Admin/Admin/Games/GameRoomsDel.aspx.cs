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

public partial class Admin_Games_GameRoomsDel : AdminBasePage
{
    string DelID;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

		string tmp = CommonManager.Web.Request( "sid", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			DelID = tmp;//Limit.getFormValue("sid");

        string sql = "delete from [TGameRoomInfo] Where id='" + Convert.ToInt32(DelID) + "'  delete from TgameroomBase where roomid='"+Convert.ToInt32(DelID)+"'";
		//sqlconn.sqlReader(sql);
		//Limit.outMsgBox( "温馨提示：\\n\\n删除成功！", "GameRooms.aspx", true );
		DbSession.Default.FromSql( sql ).Execute();
		Response.Write( "<script>alert('删除操作成功！');location.href='GameRooms.aspx';</script>" );
    }
}
