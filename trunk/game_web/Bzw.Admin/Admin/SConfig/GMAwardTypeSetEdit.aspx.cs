using System;
using System.Collections.Generic;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using Bzw.Data;
using BCST.Common;

namespace Bzw.Web.Admin.SConfig
{
	public partial class GMAwardTypeSetEdit : AdminBasePage
	{
		protected string id = CommonManager.Web.Request( "id", "" );
		protected string type = CommonManager.Web.Request( "type", "" );
		protected string sql = string.Empty;
		protected void Page_Load( object sender, EventArgs e )
		{
			if( !IsPostBack )
			{
				BindPropData();
				if( type == "edit" )
				{
					Button1.Text = "编 辑";
					BindData();
				}
			}
		}
		//编辑时绑定数据
		protected void BindData()
		{
			sql="select * from TGM＿AwardType where SeriNo=@Id";
			DataTable dt = DbSession.Default.FromSql( sql )
				.AddInputParameter( "@Id", DbType.String, id )
				.ToDataTable();
			if( dt.Rows.Count > 0 )
			{
				txtMoney.Text = dt.Rows[0]["Gold"].ToString();
				//绑定赠送的道具及数量
				for( int i = 1; i < 5; i++ )
				{
					TextBox tb = (TextBox)FindControl( "txtCount" + i );
					tb.Text = dt.Rows[0]["PropCount"+i].ToString();
					DropDownList ddl = (DropDownList)FindControl( "ddlProp" + i );
					ddl.SelectedValue = dt.Rows[0]["PropID" + i].ToString();
				}
			}
		}
		//绑定道具列表
		protected void BindPropData()
		{
			sql = "select * from TPropDefine";
			DataTable dt = DbSession.Default.FromSql( sql ).ToDataTable();
			if( dt.Rows.Count > 0 )
			{
				for( int i = 1; i < 5; i++ )
				{
					DropDownList ddl=(DropDownList)FindControl( "ddlProp" + i );
					for( int j = 0; j < dt.Rows.Count; j++ )
					{
						ddl.Items.Add( new ListItem( dt.Rows[j]["PropName"].ToString(), dt.Rows[j]["PropID"].ToString() ) );
					}		
				}						
			}
		}

		protected void Button1_Click( object sender, EventArgs e )
		{
			string money = txtMoney.Text;
			string propID1 = ddlProp1.SelectedValue;
			string propID2 = ddlProp2.SelectedValue;
			string propID3 = ddlProp3.SelectedValue;
			string propID4 = ddlProp4.SelectedValue;
			string count1 = txtCount1.Text;
			string count2 = txtCount2.Text;
			string count3 = txtCount3.Text;
			string count4 = txtCount4.Text;
			string result = string.Empty;
			if( count1 == "" )
			{
				count1 = "0";
			}
			if( count2 == "" )
			{
				count2 = "0";
			}
			if( count3 == "" )
			{
				count3 = "0";
			}
			if( count4 == "" )
			{
				count4 = "0";
			}
			//若选定了道具，则对应的数量必须大于0
			if( ( Convert.ToInt32( propID1 ) > 0 && count2 == "" ) || ( Convert.ToInt32( propID2 ) > 0 && count2 == "" ) || ( Convert.ToInt32( propID3 ) > 0 && count3 == "" ) || ( Convert.ToInt32( propID4 ) > 0 && count4 == "" ) )
			{
				CommonManager.Web.RegJs( this, "alert('选定的道具数不能为空')", false );
				return;
			}
			if( ( Convert.ToInt32( propID1 ) == 0 &&  count1 != "0" ) || ( Convert.ToInt32( propID2 ) == 0 &&  count2 != "0" ) || ( Convert.ToInt32( propID3 ) == 0 &&  count3 != "0" ) || ( Convert.ToInt32( propID4 ) == 0  && count4 != "0" ) )
			{
				CommonManager.Web.RegJs( this, "alert('需选定道具才可输入数量')", false );
				return;
			}
			//验证数据
			if( type == "edit" )		
			{
				//更新
				sql = "update TGM＿AwardType set Gold=@Gold,PropID1=@PropID1,PropCount1=@PropCount1,PropID2=@PropID2,PropCount2=@PropCount2,PropID3=@PropID3,PropCount3=@PropCount3,";
				sql += "PropID4=@PropID4,PropCount4=@PropCount4 where SeriNo=@Id";
				result = DbSession.Default.FromSql( sql )
					.AddInputParameter( "@Gold", DbType.Int32, money )
					.AddInputParameter( "@PropID1", DbType.Int32, propID1 )
					.AddInputParameter( "@PropCount1", DbType.Int32, count1 )
					.AddInputParameter( "@PropID2", DbType.Int32, propID2 )
					.AddInputParameter( "@PropCount2", DbType.Int32, count2 )
					.AddInputParameter( "@PropID3", DbType.Int32, propID3 )
					.AddInputParameter( "@PropCount3", DbType.Int32, count3 )
					.AddInputParameter( "@PropID4", DbType.Int32, propID4 )
					.AddInputParameter( "@PropCount4", DbType.Int32, count4 )
					.AddInputParameter( "@Id", DbType.Int32, id )
					.Execute().ToString();
				if( result == "1" )
				{
					CommonManager.Web.RegJs( this, "alert('恭喜您！修改成功')", false );
					BindData();
				}
			}
			else
			{
				//添加
				sql = "select top 1 @SeriNO=SeriNO+1 from TGM＿AwardType order by SeriNO desc ";
				sql += "if not exists(select *  from TGM＿AwardType) set @SeriNo=1";
				sql += "insert into TGM＿AwardType values(@SeriNO,@Gold,@PropID1,@PropCount1,@PropID2,@PropCount2,@PropID3,@PropCount3,@PropID4,@PropCount4)";
				result = DbSession.Default.FromSql( sql )
					.AddInputParameter( "@Gold", DbType.Int32, money )
					.AddInputParameter( "@PropID1", DbType.Int32, propID1 )
					.AddInputParameter( "@PropCount1", DbType.Int32, count1 )
					.AddInputParameter( "@PropID2", DbType.Int32, propID2 )
					.AddInputParameter( "@PropCount2", DbType.Int32, count2 )
					.AddInputParameter( "@PropID3", DbType.Int32, propID3 )
					.AddInputParameter( "@PropCount3", DbType.Int32, count3 )
					.AddInputParameter( "@PropID4", DbType.Int32, propID4 )
					.AddInputParameter( "@PropCount4", DbType.Int32, count4 )
					.AddInputParameter( "@SeriNO",DbType.Int32,0)
					.Execute().ToString();
				if( result == "1" )
				{
					CommonManager.Web.RegJs( this, "alert('恭喜您！添加成功')", false );
				}
			}
		}
	}
}
