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

using Bzw.Entities;
using Bzw.Data;
using Utility;

public partial class Admin_Games_GameBattleRoomsWrite : AdminBasePage
{
	

    //protected int IntParam
    //{
    //    get
    //    {
    //        string tmp = CommonManager.Web.Request( "params", "" );
    //        if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
    //            return 0;
    //        return int.Parse( tmp );
    //    }
    //}

	protected void Page_Load( object sender, EventArgs e )
	{		
		AdminPopedom.IsHoldModel( "06" );

		if( IntParam != 0 )
		{
			TBattleRoomInfo model = DbSession.Default.Get<TBattleRoomInfo>( TBattleRoomInfo._.BattleRoomID == IntParam );
			if( model != null && !IsPostBack )
			{
				txtRoomName.Text = model.RoomName;
				txtBeginTime.Text = model.BeginTime.ToString("yyyy-MM-dd HH:mm:ss");
				txtEndTime.Text = model.EndTime.ToString( "yyyy-MM-dd HH:mm:ss" );
			}
		}
	}
	
	protected void btnSubmit_Click( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;
		if( !IsValid )
			return;

		TBattleRoomInfo model;
		string log = "";
		if( IntParam == 0 )
		{
			//添加
			model = new TBattleRoomInfo();
			int? mid = (int?)DbSession.Default.Max<TBattleRoomInfo>( TBattleRoomInfo._.BattleRoomID, new WhereClip( "" ) );
			model.BattleRoomID = mid.HasValue ? mid.Value + 1 : 1;
			log = "修改混战场信息，ID号为：" + model.BattleRoomID;
		}
		else
		{
			//修改
			model = DbSession.Default.Get<TBattleRoomInfo>(TBattleRoomInfo._.BattleRoomID == IntParam);
			model.Attach();
			log = "添加混战场房间";
		}
		model.RoomName = txtRoomName.Text.Trim();
		model.BeginTime = DateTime.Parse(txtBeginTime.Text.Trim());
		model.EndTime = DateTime.Parse(txtEndTime.Text.Trim());

		DbSession.Default.Save<TBattleRoomInfo>( model );
		//AdminLog.Default.Add( Session["AdminName"].ToString(), log );
		string adminName = AdminInfo["UserName"].ToString();
		string system = Common.GetOS;
		new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, log, 1 );
		CommonManager.Web.RegJs( this, "alert('操作成功！');LocationTo('GameBattleRooms.aspx');", false );
	}
}
