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

public partial class Admin_Users_UserGameSeachList_xg : AdminBasePage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("04");

		string tmp = CommonManager.Web.Request("id","");
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			CommonManager.Web.RegJs( this, "alert('参数错误！');history.back();", false );
			return;
		}

		string sql = "SELECT * FROM TChangeRecordUser,Tusers,TChangeRecord,TGameRoomInfo WHERE RecordIndex= @RecordIndex and TChangeRecordUser.UserID=Tusers.UserID and TChangeRecordUser.RecordIndex=TChangeRecord.ID and TChangeRecord.RoomID=TGameRoomInfo.RoomID";
		DataTable dt = DbSession.Default.FromSql( sql ).AddInputParameter( "@RecordIndex", DbType.Int32, tmp ).ToDataTable();
		if( dt.Rows.Count > 0 )
		{
			rptDataList.DataSource = dt;
			rptDataList.DataBind();
			ltNonData.Visible = false;
			rptDataList.Visible = true;
		}
		else
		{
			rptDataList.Visible = false;
			ltNonData.Visible = true;
		}
    }
}
