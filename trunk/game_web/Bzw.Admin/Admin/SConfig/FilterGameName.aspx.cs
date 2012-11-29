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

public partial class Admin_SConfig_FilterGameName : AdminBasePage
{	
	BLL.Member member = new BLL.Member();
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "12" );
		//Left Listbox item was double click.
		if( Request.Params["listLeftHidden"] != null
	 && (string)Request.Params["listLeftHidden"] == "leftdoubleclicked" )
		{
			if( listLeft.SelectedIndex > -1 )
			{
				listRight.Items.Add( new ListItem( listLeft.SelectedItem.ToString(), listLeft.SelectedValue ) );
				if( listLeft.Items.Count > 0 )
					listLeft.Items.Remove( listLeft.SelectedItem );
			}
		}
		//Right Listbox item was double click.
		if( Request.Params["listRightHidden"] != null
	 && (string)Request.Params["listRightHidden"] == "rightdoubleclicked" )
		{
			if( listRight.SelectedIndex > -1 )
			{
				listLeft.Items.Add( new ListItem( listRight.SelectedItem.ToString(), listRight.SelectedValue ) );
				if( listRight.Items.Count > 0 )
					listRight.Items.Remove( listRight.SelectedItem );
			}
		}
		if( !IsPostBack )
		{

			//1.
			DataTable dt = member.GetGameNameForAward();
			if( dt.Rows.Count > 0 )
			{
				foreach( DataRow dr in dt.Rows )
				{
					lbaward.Text += "&nbsp;" + dr["ComName"].ToString();
				}
			}
			dt.Clear();
			//2.
			dt = member.GetFilterGameNameForAward();
			if( dt.Rows.Count > 0 )
			{
				foreach( DataRow dr in dt.Rows )
				{
					lbfiteraward.Text += "&nbsp;" + dr["ComName"].ToString();
				}
			}
			dt.Clear();
			//3.
			dt = member.GetGameNameForExtent();
			if( dt.Rows.Count > 0 )
			{
				foreach( DataRow dr in dt.Rows )
				{
					lbextent.Text += "&nbsp;" + dr["ComName"].ToString();
				}
			}
			dt.Clear();
			//4.
			dt = member.GetFilterGameNameForExtent();
			if( dt.Rows.Count > 0 )
			{
				foreach( DataRow dr in dt.Rows )
				{
					lbfiterextent.Text += "&nbsp;" + dr["ComName"].ToString();
				}
			}
			dt.Clear();

			BindData();
		}
	}

	protected void BindData()
	{
		DataTable dt = new DataTable();
		string type = CommonManager.Web.Request( "type", "" );
		if( CommonManager.String.IsInteger( type ) && type.Equals( "0" ) )
		{
			//Award 			
			dt = member.GetGameNameForAward();
			if( dt.Rows.Count > 0 )
			{
				for( int i = 0; i < dt.Rows.Count; i++ )
					listLeft.Items.Add( new ListItem( dt.Rows[i]["ComName"].ToString(), dt.Rows[i]["NameID"].ToString() ) );
			}
			dt.Clear();

			//		
			dt = member.GetFilterGameNameForAward();
			if( dt.Rows.Count > 0 )
			{
				for( int i = 0; i < dt.Rows.Count; i++ )
					listRight.Items.Add( new ListItem( dt.Rows[i]["ComName"].ToString(), dt.Rows[i]["NameID"].ToString() ) );
			}
			dt.Clear();
            this.map.Style.Add("display", "block");
		}

		if( CommonManager.String.IsInteger( type ) && type.Equals( "1" ) )
		{
			//extent 			
			dt = member.GetGameNameForExtent();
			if( dt.Rows.Count > 0 )
			{
				for( int i = 0; i < dt.Rows.Count; i++ )
					listLeft.Items.Add( new ListItem( dt.Rows[i]["ComName"].ToString(), dt.Rows[i]["NameID"].ToString() ) );
			}
			dt.Clear();

			//			
			dt = member.GetFilterGameNameForExtent();
			if( dt.Rows.Count > 0 )
			{
				for( int i = 0; i < dt.Rows.Count; i++ )
					listRight.Items.Add( new ListItem( dt.Rows[i]["ComName"].ToString(), dt.Rows[i]["NameID"].ToString() ) );
			}
			dt.Clear();
            this.map.Style.Add("display", "block");
		}
	}

	protected void EditFilt( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;

		string nameID = string.Empty;
		foreach( ListItem li in listRight.Items )
		{
			if( string.IsNullOrEmpty( nameID ) )
				nameID = li.Value;
			else
				nameID += "," + li.Value;
		}
		string type = CommonManager.Web.Request( "type", "" );
		string sql = string.Empty;
		if( !CommonManager.String.IsInteger( type ) )
			return;
		if( type.Equals( "0" ) )
		{
			sql="update Web_Config set GameNameID=@GameNameID where Id = 1";
		}
		else if( type.Equals( "1" ) )
		{
			sql = "update Web_Config set TG_GameNameID=@GameNameID where Id = 1";
		}
		else
		{
			Alert( "温馨提示：\\n\\n设置失败！", "FilterGameName.aspx" );
		}
		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@GameNameID", DbType.String, nameID )
			.Execute();
		Alert( "温馨提示：\\n\\n设置成功！", "FilterGameName.aspx" );
	}

	protected void btnToRight_Click( object sender, EventArgs e )
	{
		int i = 0;
		while( i < listLeft.Items.Count )
		{
			if( listLeft.Items[i].Selected )
			{
				this.listRight.Items.Add( new ListItem( listLeft.Items[i].Text, listLeft.Items[i].Value ) );
				listLeft.Items.Remove( listLeft.Items[i] );
			}
			else
				i += 1;
		}
	}
	protected void btnToLeft_Click( object sender, EventArgs e )
	{
		int i = 0;
		while( i < listRight.Items.Count )
		{
			if( listRight.Items[i].Selected )
			{
				listLeft.Items.Add( new ListItem( listRight.Items[i].Text, listRight.Items[i].Value ) );
				listRight.Items.Remove( listRight.Items[i] );
			}
			else
				i += 1;
		}
	}
}
