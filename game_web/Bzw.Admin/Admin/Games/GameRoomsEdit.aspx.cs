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

public partial class Admin_Games_GameRoomsEdit : AdminBasePage
{
    string RoomsId;
    public string Snameid, SRoomName, SServiceIP, SServerInfoID, SDeskCount, SMaxPeople, Stax, SBasePoint, SLessPoint, SMaxPoint, SExercisePoint, SContestID;
    public string SRoomRule, SIDSort, SLockTable, SMatchTable, SIPRuleTable, SUserNameRuleTable, SbEnableRoom, SServiceName, SVersion;
    public string SRoomWelcome, SRallWelcome, SRunPublish, SComType, RoomID;

    protected string SBattleRoomID = "", SBattleMatchTable = "", TaxType = "1", Type;

    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");
        TaxType = UiCommon.StringConfig.RoomTaxSelected;
        if (string.IsNullOrEmpty(TaxType) || !CommonManager.String.IsInteger(TaxType))
            TaxType = "1";


        string tmp = CommonManager.Web.Request("sid", "");
        if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp))
        {
            Alert("请勿非法操作！", null);
            return;
        }
        else
            RoomsId = tmp;//Limit.getFormValue("sid");

        #region 大类
        DataTable sdb = new DataTable();
        string sqlb = "select n.*,nc.KindName,nc.KindId as ncKindId from [TGameRoomInfo] as n left outer join [TGameKindInfo] as nc on n.GameKindID=nc.KindId where n.id='" + RoomsId + "'";
        sdb = DbSession.Default.FromSql(sqlb).ToDataTable();//sqlconn.sqlReader(sqlb);
        if (sdb.Rows.Count > 0)
        {
           // this.kindid.Items.Add(new ListItem(sdb.Rows[0]["KindName"].ToString(), sdb.Rows[0]["ncKindId"].ToString()));
        }
       

        DataTable sdBig = new DataTable();
        string sqlBig = "select * from TGameKindInfo order by IDSort DESC";
        sdBig = DbSession.Default.FromSql(sqlBig).ToDataTable();//sqlconn.sqlReader(sqlBig);
        if (sdBig.Rows.Count > 0)
        {
            this.kindid.DataBind();
            for (int i = 0; i < sdBig.Rows.Count; i++)
            {
                this.kindid.Items.Add(new ListItem(sdBig.Rows[i]["kindname"].ToString(), sdBig.Rows[i]["kindid"].ToString()));
            }
        }
        sdBig.Clear();
        this.kindid.SelectedValue = sdb.Rows[0]["ncKindId"].ToString();
        sdb.Clear();
        #endregion

        #region 小类 及 其他数据
        DataTable sd = new DataTable();
        string sql = "select n.*,nc.*,rb.*,tb.*,tm.*   from [TGameRoomInfo] as n left outer join [TGameNameInfo] as nc on nc.Nameid=n.GameNameID left outer join [TGameRoomBase] as rb on rb.RoomID=n.RoomID left outer join [TGameRoomTable] as tb on tb.RoomID=n.RoomID left outer join [TGameRoomMsg] as tm on tm.RoomID=n.RoomID where n.id='" + RoomsId + "'";
        sd = DbSession.Default.FromSql(sql).ToDataTable();//sqlconn.sqlReader(sql);

        if (sd.Rows.Count > 0)
        {
            //Response.Write("GameTypeID:" + sd.Rows[0]["GameTypeID"].ToString());
            SComType = sd.Rows[0]["GameTypeID"].ToString();
            this.ComName.Items.Add(new ListItem(sd.Rows[0]["ComName"].ToString(), sd.Rows[0]["Nameid"].ToString()));
            this.Snameid = sd.Rows[0]["GameNameID"].ToString();
            this.SRoomName = sd.Rows[0]["RoomName"].ToString();
            this.SServiceIP = sd.Rows[0]["ServerIP"].ToString();
            this.SServerInfoID = sd.Rows[0]["ServerInfoID"].ToString();
            this.SDeskCount = sd.Rows[0]["DeskCount"].ToString();
            this.SMaxPeople = sd.Rows[0]["MaxPeople"].ToString();
            this.SBasePoint = sd.Rows[0]["BasePoint"].ToString();
            this.SLessPoint = sd.Rows[0]["LessPoint"].ToString();
            this.SRoomRule = sd.Rows[0]["RoomRule"].ToString();
            this.SIDSort = sd.Rows[0]["IDSort"].ToString();
            this.SLockTable = sd.Rows[0]["TableLock"].ToString();
            this.SMatchTable = sd.Rows[0]["TableMatch"].ToString();
            this.SIPRuleTable = sd.Rows[0]["TableIPRule"].ToString();
            this.SUserNameRuleTable = sd.Rows[0]["TableUserNameRule"].ToString();
            this.SbEnableRoom = sd.Rows[0]["EnableRoom"].ToString();
            this.SServiceName = sd.Rows[0]["ServiceName"].ToString();
            this.SVersion = sd.Rows[0]["Version"].ToString();
            this.SVersion = Convert.ToInt32((Convert.ToInt32(this.SVersion) / 65536)) + "." + (Convert.ToInt32(this.SVersion) % 65536);
            this.SRoomWelcome = sd.Rows[0]["RoomWelcome"].ToString();
            this.SRallWelcome = sd.Rows[0]["RallWelcome"].ToString();
            this.SRunPublish = sd.Rows[0]["RunPublish"].ToString();
            this.SBattleRoomID = sd.Rows[0]["BattleRoomID"].ToString();
            this.SBattleMatchTable = sd.Rows[0]["BattleMatchTable"].ToString();
            this.txtPlayCounts_1.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayCounts_1"].ToString()) ? "0" : sd.Rows[0]["PlayCounts_1"].ToString();
            this.txtPlayCounts_2.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayCounts_2"].ToString()) ? "0" : sd.Rows[0]["PlayCounts_2"].ToString();
            this.txtPlayCounts_3.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayCounts_3"].ToString()) ? "0" : sd.Rows[0]["PlayCounts_3"].ToString();
            this.txtPlayCountsMoney_1.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayCountsMoney_1"].ToString()) ? "0" : sd.Rows[0]["PlayCountsMoney_1"].ToString();
            this.txtPlayCountsMoney_2.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayCountsMoney_2"].ToString()) ? "0" : sd.Rows[0]["PlayCountsMoney_2"].ToString();
            this.txtPlayCountsMoney_3.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayCountsMoney_3"].ToString()) ? "0" : sd.Rows[0]["PlayCountsMoney_3"].ToString();
            this.txtPlayTimes.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayTimes"].ToString()) ? "0" : "" + Convert.ToInt32(sd.Rows[0]["PlayTimes"].ToString()) / 60;
            this.txtPlayTimesMoney.Text = string.IsNullOrEmpty(sd.Rows[0]["PlayTimesMoney"].ToString()) ? "0" : sd.Rows[0]["PlayTimesMoney"].ToString();
            this.SMaxPoint = sd.Rows[0]["MaxPoint"].ToString();
            Stax = sd.Rows[0]["tax"].ToString();
            this.SContestID = sd.Rows[0]["ContestID"].ToString();
            this.SExercisePoint = string.IsNullOrEmpty(sd.Rows[0]["ExercisePoint"].ToString()) ? "0" : sd.Rows[0]["ExercisePoint"].ToString();
            this.txtSendTimeLength.Text = string.IsNullOrEmpty(sd.Rows[0]["SendTimeLength"].ToString()) ? "0" : sd.Rows[0]["SendTimeLength"].ToString();
            this.txtSendCount.Text = string.IsNullOrEmpty(sd.Rows[0]["SendCount"].ToString()) ? "0" : sd.Rows[0]["SendCount"].ToString();
            if (TaxType.Equals("1"))
            {
                if ((Convert.ToInt32(SRoomRule) & (int)(0x00020000L)) > 0)//根据房间规则确定是税率还是门票
                {
                    //门票
                    Type = "0";
                }
                else
                {
                    Type = "1";
                }
            }
            RoomID = sd.Rows[0]["RoomID"].ToString();
            if (!string.IsNullOrEmpty(sd.Rows[0]["RoomPassword"].ToString()))
            {
                Session["password"] = sd.Rows[0]["RoomPassword"].ToString();
                ltMsg.Text = "此房间已设置密码。修改密码请直接填写，清空密码请打钩:";
                cbClearPassword.Visible = true;
            }
            else
            {
                if (Session["password"] != null)
                    Session["password"] = null;
            }
        }
        //判断此房间是否是租赁房间
        string tenancyID = sd.Rows[0]["tenancyID"].ToString();
        if (tenancyID != "0" && !string.IsNullOrEmpty(tenancyID) && Utility.Common.IsIntegrity(tenancyID))
        {
            ShowUser.Visible = true;
            DataTable dt8 = DbSession.Default.FromSql("select UserID,UserName from Web_VApplyVipRoom where id=" + tenancyID).ToDataTable();
            if (dt8.Rows.Count > 0)
            {

                lblUserID.Text = dt8.Rows[0]["UserID"].ToString();
                lblUserName.Text = dt8.Rows[0]["UserName"].ToString();

            }
            dt8.Clear();
        }
        else
        {
            ShowUser.Visible = false;
        }

        sd.Clear();


        DataTable sd2 = new DataTable();
        string sql2 = "select NameID,ComName from TGameNameInfo order by NameID desc";
        sd2 = DbSession.Default.FromSql(sql2).ToDataTable();//sqlconn.sqlReader(sql2);
        if (sd2.Rows.Count > 0)
        {
            this.ComName.DataBind();
            for (int i = 0; i < sd2.Rows.Count; i++)
            {
                this.ComName.Items.Add(new ListItem(sd2.Rows[i]["ComName"].ToString(), sd2.Rows[i]["NameID"].ToString()));
            }
        }
        sd2.Clear();
        #endregion

    }

    protected void EditGameRooms(object sender, EventArgs e)
    {
        string sqlComType, sqlkindid, sqlComName, sqlnameid, sqlRoomName, sqlServiceIP, sqlServerInfoID, sqlDeskCount, sqlMaxPeople, sqltax, sqlExercisePoint, sqlContestID;
        string sqlBasePoint, sqlLessPoint, sqlRoomRule, sqlIDSort, sqlLockTable, sqlMatchTable, sqlIPRuleTable, sqlUserNameRuleTable, sqlbEnableRoom;
        string sqlServiceName, sqlVersion, sqlRoomWelcome, sqlRallWelcome, sqlRunPublish, sqlTaxType, sqlRoomPassword;
        string sqlPlayTimes, sqlPlayTimesMoney, sqlPlayCounts_1, sqlPlayCountsMoney_1, sqlPlayCounts_2, sqlPlayCountsMoney_2, sqlPlayCounts_3, sqlPlayCountsMoney_3, sqlMaxPoint;
        //Limit.ToString().ToLower();
        string sqlSendTimeLength, sqlSendCount;
        sqlMaxPoint = CommonManager.Web.RequestForm("MaxPoint", "");
        sqlComType = CommonManager.Web.RequestForm("ComType", "");//Limit.editCharacter( Limit.getFormValue( "ComType" ) ).ToString();
        sqlkindid = this.kindid.Text.ToString();
        if (sqlkindid.ToString() == "")
        {
            Alert("温馨提示：\\n\\n游戏类别不能为空！", null);
            return;
        }

        sqlServerInfoID = CommonManager.Web.RequestForm("ServerInfoID", "");
        sqlRoomName = CommonManager.Web.RequestForm("RoomName", "");//Limit.editCharacter( Limit.getFormValue( "RoomName" ) ).ToString();
        if (sqlRoomName.ToString() == "")
        {
            Alert("温馨提示：\\n\\n请输入房间名称！", null);
            return;
        }
        if (sqlRoomName.ToString().Length > 30)
        {
            Alert("温馨提示：\\n\\n房间名称最多30个字符", null);
            return;
        }
        sqlServiceIP = CommonManager.Web.RequestForm("ServiceIP", "");//Limit.editCharacter( Limit.getFormValue( "ServiceIP" ) ).ToString();
        if (sqlServiceIP.ToString() == "")
        {
            Alert("温馨提示：\\n\\n请输入服务器IP！", null);
            return;
        }
        sqlDeskCount = CommonManager.Web.RequestForm("DeskCount", "");//Limit.editCharacter( Limit.getFormValue( "DeskCount" ) ).ToString();
        if (sqlDeskCount.ToString() == "")
        {
            Alert("温馨提示：\\n\\n桌子人数不能为空！", null);
            return;
        }
        if (!Utility.Common.IsPositiveNumber(sqlDeskCount))
        {
            Alert("温馨提示：\\n\\n桌子人数只能为非负数！", null);
            return;
        }
        if (Convert.ToInt32(sqlDeskCount) > 60)
        {
            Alert("温馨提示：\\n\\n桌子人数最大值为60！", null);
            return;
        }
        sqlMaxPeople = CommonManager.Web.RequestForm("MaxPeople", "");//Limit.editCharacter( Limit.getFormValue( "MaxPeople" ) ).ToString();
        if (!Utility.Common.IsPositiveNumber(sqlMaxPeople))
        {
            CommonManager.Web.RegJs(this, "alert('[人数上限]必须为非负数！');location.href=location.href;", false);
            return;
        }



        sqlBasePoint = CommonManager.Web.RequestForm("BasePoint", "");//Limit.editCharacter( Limit.getFormValue( "BasePoint" ) ).ToString();
        if (!Utility.Common.IsPositiveNumber(sqlBasePoint))
        {
            CommonManager.Web.RegJs(this, "alert('[倍数]必须为非负数！');location.href=location.href;", false);
            return;
        }
        sqlLessPoint = CommonManager.Web.RequestForm("LessPoint", "");//Limit.editCharacter( Limit.getFormValue( "LessPoint" ) ).ToString();
        if (!Utility.Common.IsPositiveNumber(sqlLessPoint))
        {
            CommonManager.Web.RegJs(this, "alert('[最少金币限制]必须为非负数！');location.href=location.href;", false);
            return;
        }


        sqlRoomRule = CommonManager.Web.RequestForm("RoomRule", "");//Limit.editCharacter( Limit.getFormValue( "RoomRule" ) ).ToString();
        if (string.IsNullOrEmpty(sqlRoomRule))
        {
            CommonManager.Web.RegJs(this, "alert('[游戏规则]不能为空！');location.href=location.href;", false);
            return;
        }
        /*sqlTaxType = "0";// CommonManager.Web.RequestForm( "raTaxType", "" );

        string tempTax = "";
        if( sqlTaxType == "0" )//如果选中的门票就不要判断税率的值，并将税率给默认值0   周圣华 2010-08-26
        {
            tempTax = CommonManager.Web.RequestForm( "Ticket", "" );
            sqlRoomRule = ( Convert.ToInt32( sqlRoomRule ) | ( int )( 0x00020000L ) ).ToString();  //根据潘鹏的意见，门票只要将房间规则和0x00020000L按位与预算得到的房间规则。在C++程序中就能判断是门票

        }
        else
        {
            tempTax = CommonManager.Web.RequestForm( "TaxPercent", "" );//Limit.editCharacter( Limit.getFormValue( "tax" ) ).ToString();
            sqlRoomRule = ( Convert.ToInt32( sqlRoomRule ) & ( int )( 0x0001FFFFL ) ).ToString();
        }*/
        sqlTaxType = CommonManager.Web.RequestForm("selTaxType", "");

        if (TaxType.Equals("1"))//显示门票和税率的选择项
        {
            if (sqlTaxType == "0")//如果选中的门票就不要判断税率的值，并将税率给默认值0   周圣华 2010-08-26
            {
                sqlRoomRule = (Convert.ToInt32(sqlRoomRule) | (int)(0x00020000L)).ToString();  //根据潘鹏的意见，门票只要将房间规则和0x00020000L按位与预算得到的房间规则。在C++程序中就能判断是门票 周圣华 2010-08-27
            }
            else
            {
                sqlRoomRule = (Convert.ToInt32(sqlRoomRule) & (long)(0xFFFDFFFFL)).ToString();
            }
        }
        else   //只显示门票
        {
            sqlRoomRule = (Convert.ToInt32(sqlRoomRule) | (int)(0x00020000L)).ToString();
        }

        string tempTax = CommonManager.Web.RequestForm("txtTax", "");

        if (!Utility.Common.IsPositiveNumber(tempTax))
        {
            CommonManager.Web.RegJs(this, "alert('房间收费必须为非负数！');location.href=location.href;", false);
            return;
        }

        sqltax = tempTax;

        sqlIDSort = CommonManager.Web.RequestForm("IDSort", "");//Limit.editCharacter( Limit.getFormValue( "IDSort" ) ).ToString();
        if (!Utility.Common.IsPositiveNumber(sqlIDSort))
        {
            CommonManager.Web.RegJs(this, "alert('[房间排序]必须为非负数！');location.href=location.href;", false);
            return;
        }
        sqlbEnableRoom = CommonManager.Web.RequestForm("bEnableRoom", "");//Limit.editCharacter( Limit.getFormValue( "bEnableRoom" ) ).ToString();
        sqlServiceName = CommonManager.Web.RequestForm("ServiceName", "");//Limit.editCharacter( Limit.getFormValue( "ServiceName" ) ).ToString();
        if (sqlServiceName.ToString() == "")
        {
            Alert("温馨提示：\\n\\n服务器DLL名称不能为空！", null);
            return;
        }
        sqlVersion = CommonManager.Web.RequestForm("Version", "");//Limit.editCharacter( Limit.getFormValue( "Version" ) ).ToString();

        string battleRoomID = CommonManager.Web.RequestForm("txtBattleRoomID", "");
        string battleMatchTable = CommonManager.Web.RequestForm("txtBattleMatchTable", "");
        if (battleRoomID == "0")
        {
            battleRoomID = "0";
            battleMatchTable = "TBattleMatchTable";
        }
        else if (CommonManager.String.IsInteger(battleRoomID) && (int.Parse(battleRoomID) > 0) && battleRoomID != SBattleRoomID)
        {
            string sqlbtr = "select * from [TBattleRoomInfo] where BattleRoomID=" + battleRoomID;
            DataTable tmpBTR = DbSession.Default.FromSql(sqlbtr).ToDataTable();//sqlconn.sqlReader( sqlbtr );
            if (tmpBTR.Rows.Count <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('找不到您输入的混战房间ID，请重新核对！');location.href=location.href;", true);

                return;
            }
            sqlbtr = "select count(id) from TGameRoomInfo where BattleRoomID=" + battleRoomID;
            tmpBTR.Clear();
            tmpBTR = DbSession.Default.FromSql(sqlbtr).ToDataTable();// sqlconn.sqlReader( sqlbtr );
            if (tmpBTR.Rows.Count > 0 && ((int)tmpBTR.Rows[0][0] > 0))
            {
                CommonManager.Web.RegJs(this, "alert('您填写的混战房间id已经被用在别的房间了，请重新输入！');location.href=location.href;", true);

                return;
            }
            if (string.IsNullOrEmpty(battleMatchTable))
            {
                battleMatchTable = "TBattleMatchTable";
            }
        }
        else
        {
            battleRoomID = SBattleRoomID;
            battleMatchTable = SBattleMatchTable;
        }

        if (sqlVersion.Length == 3)
        {
            string tma = sqlVersion.Substring(1, 1);
            if (tma == ".")
            {
                string[] versions = sqlVersion.Split('.');
                int tmversion = 0;
                tmversion = Convert.ToInt32(versions[0]) * 65536 + Convert.ToInt32(versions[1]);
                sqlVersion = tmversion.ToString();
            }
            else
            {
                Alert("温馨提示：\\n\\n版本号格式有误！", null);
                return;
            }
        }
        else
        {
            Alert("温馨提示：\\n\\n版本号格式有误！", null);
            return;
        }

        sqlRoomWelcome = CommonManager.Web.RequestForm("RoomWelcome", "");//Limit.editCharacter( Limit.getFormValue( "RoomWelcome" ) ).ToString();
        sqlRallWelcome = CommonManager.Web.RequestForm("RallWelcome", "");//Limit.editCharacter( Limit.getFormValue( "RallWelcome" ) ).ToString();
        sqlRunPublish = CommonManager.Web.RequestForm("RunPublish", "");//Limit.editCharacter( Limit.getFormValue( "RunPublish" ) ).ToString();
        if (!Utility.Common.IsPositiveNumber(sqlRunPublish))
        {
            CommonManager.Web.RegJs(this, "alert('[逃跑]必须为非负数！');location.href=location.href;", false);
            return;
        }
        sqlComName = CommonManager.Web.RequestForm("ComName", "");
        sqlLockTable = CommonManager.Web.RequestForm("LockTable", "");
        sqlIPRuleTable = CommonManager.Web.RequestForm("IPRuleTable", "");
        sqlMatchTable = CommonManager.Web.RequestForm("MatchTable", "");
        sqlUserNameRuleTable = CommonManager.Web.RequestForm("UserNameRuleTable", "");
        if (cbClearPassword.Checked)
            sqlRoomPassword = "";
        else
        {
            sqlRoomPassword = CommonManager.Web.RequestForm("RoomPassword", "");
            if (!string.IsNullOrEmpty(sqlRoomPassword))
            {

                sqlRoomPassword = CommonManager.String.EncryptMD5SystemDefaultMethod(sqlRoomPassword, false, true);//伯乐棋牌中增加密码房间
            }
            else
                sqlRoomPassword = Session["password"] == null ? "" : Session["password"].ToString();
        }
        //增加在线时长送金币，局数送金币
        sqlPlayTimes = CommonManager.Web.RequestForm("txtPlayTimes", "");
        sqlPlayTimesMoney = CommonManager.Web.RequestForm("txtPlayTimesMoney", "");
        if (!Utility.Common.IsPositiveNumber(sqlPlayTimes) || !Utility.Common.IsPositiveNumber(sqlPlayTimesMoney))
        {
            Alert("温馨提示：\\n\\n在线时长和所送金币数必须为非负数！", null);
            return;
        }
        sqlPlayCounts_1 = CommonManager.Web.RequestForm("txtPlayCounts_1", "");
        sqlPlayCounts_2 = CommonManager.Web.RequestForm("txtPlayCounts_2", "");
        sqlPlayCounts_3 = CommonManager.Web.RequestForm("txtPlayCounts_3", "");
        if (!Utility.Common.IsPositiveNumber(sqlPlayCounts_1) || !Utility.Common.IsPositiveNumber(sqlPlayCounts_2) || !Utility.Common.IsPositiveNumber(sqlPlayCounts_3))
        {
            Alert("温馨提示：\\n\\n游戏局数必须为非负数！", null);
            return;
        }
        sqlPlayCountsMoney_1 = CommonManager.Web.RequestForm("txtPlayCountsMoney_1", "");
        sqlPlayCountsMoney_2 = CommonManager.Web.RequestForm("txtPlayCountsMoney_2", "");
        sqlPlayCountsMoney_3 = CommonManager.Web.RequestForm("txtPlayCountsMoney_3", "");
        if (!Utility.Common.IsPositiveNumber(sqlPlayCountsMoney_1) || !Utility.Common.IsPositiveNumber(sqlPlayCountsMoney_2) || !Utility.Common.IsPositiveNumber(sqlPlayCountsMoney_3))
        {
            Alert("温馨提示：\\n\\n游戏局数所送金币数必须为非负数！", null);
            return;
        }
        sqlExercisePoint = CommonManager.Web.RequestForm("ExercisePoint", "0");
        if (!CommonManager.String.IsFloat(sqlExercisePoint))
        {
            Alert("温馨提示：\\n\\n练习房间进入默认金币必须为非负数！", null);
            return;
        }
        sqlSendTimeLength = CommonManager.Web.RequestForm("txtSendTimeLength", "0");
        sqlSendCount = CommonManager.Web.RequestForm("txtSendCount", "0");

        if (!Utility.Common.IsPositiveNumber(sqlSendTimeLength))
        {
            Alert("温馨提示：\\n\\n每局时长的值为大于等于0的整数！", null);
            return;
        }
        if (!Utility.Common.IsPositiveNumber(sqlSendCount))
        {
            Alert("温馨提示：\\n\\n每局时长达到时，奖励" + UiCommon.StringConfig.MoneyName + "数必须为大于等于0的数", null);
            return;
        }

        sqlContestID = CommonManager.Web.RequestForm("txtContestID", "0");
        if (CommonManager.String.IsInteger(sqlContestID) && (int.Parse(sqlContestID) > 0))
        {
            string sqlbtr = "select * from [TContestInfo] where ContestID=" + sqlContestID;
            DataTable tmpBTR = DbSession.Default.FromSql(sqlbtr).ToDataTable(); //sqlconn.sqlReader( sqlbtr );
            if (tmpBTR.Rows.Count <= 0)
            {
                CommonManager.Web.RegJs(this, "alert('找不到您输入的比赛ID，请重新核对！');location.href=location.href;", true);
                return;
            }
            //sqlbtr = "select count(roomid) from TGameRoomBase where ContestID=" + sqlContestID+" and roomid<>"+RoomsId;
            //tmpBTR.Clear();
            //tmpBTR = DbSession.Default.FromSql(sqlbtr).ToDataTable();// sqlconn.sqlReader( sqlbtr );
            //if (tmpBTR.Rows.Count > 0 && ((int)tmpBTR.Rows[0][0] > 0))
            //{
            //    CommonManager.Web.RegJs(this, "alert('您填写的比赛id已经被用在别的房间了，请重新输入！');location.href=location.href;", true);
            //    return;
            //}

        }
        else
        {
            sqlContestID = "0";

        }

        string sql = @" declare @SameRoomCount int --判断是否是万人房
                        set @SameRoomCount=1
                        declare @ContentIdOld int
                        select @ContentIdOld=contestid from tgameroombase where roomid=@RoomID
                        select @SameRoomCount=count(1) from TgameRoomBase where contestID>0 and ContestID=@ContentIdOld
                        if(@SameRoomCount>1)
                        begin
                             UPDATE [TGameRoomInfo] SET 
						    [RoomName] = @RoomName,[ServerIP] = @ServerIP,[ServerInfoID] = @ServerInfoID,
						    [GameTypeID] = @GameTypeID,[GameKindID] = @GameKindID,[GameNameID] = @GameNameID,
						    [EnableRoom] = @EnableRoom,[IDSort] = @IDSort,
						    [Version] = @Version,[ServiceName] = @ServiceName,
						    [BattleRoomID]=@BattleRoomID,[BattleMatchTable]=@BattleMatchTable,[RoomPassword]=@RoomPassword,[SendTimeLength]=@SendTimeLength,[SendCount]=@SendCount  
						     WHERE id in (select roomid from TgameRoomBase where ContestID=@ContentIdOld);

						    UPDATE [TGameRoomBase] SET 
						    [RoomRule] = @RoomRule,[DeskCount] = @DeskCount,[MaxPeople] = @MaxPeople,
						    [BasePoint] = @BasePoint,[LessPoint] = @LessPoint,[Tax] = @Tax,
						    [RunPublish] = @RunPublish,[PlayTimes]=@PlayTimes,[PlayTimesMoney]=@PlayTimesMoney,[PlayCounts_1]=@PlayCounts_1,
                            [PlayCountsMoney_1]=@PlayCountsMoney_1,[PlayCounts_2]=@PlayCounts_2,[PlayCountsMoney_2]=@PlayCountsMoney_2,
                            [PlayCounts_3]=@PlayCounts_3,  [PlayCountsMoney_3]=@PlayCountsMoney_3,[MaxPoint]=@MaxPoint,[ExercisePoint]=@ExercisePoint,ContestID=@ContestID
						    WHERE RoomID  in (select roomid from TgameRoomBase where ContestID=@ContentIdOld) ;

						    UPDATE [TGameRoomMsg] SET 
						    [RoomWelcome] = @RoomWelcome,[RallWelcome] = @RallWelcome
						    WHERE RoomID  in (select roomid from TgameRoomBase where ContestID=@ContentIdOld) ;

						    UPDATE [TGameRoomTable] SET 
						    [TableLock] = @TableLock,[TableIPRule] = @TableIPRule,[TableMatch] = @TableMatch,
						    [TableUserNameRule] = @TableUserNameRule
						    WHERE RoomID  in (select roomid from TgameRoomBase where ContestID=@ContentIdOld)
                        end
                        else
                        begin
						    UPDATE [TGameRoomInfo] SET 
						    [RoomName] = @RoomName,[ServerIP] = @ServerIP,[ServerInfoID] = @ServerInfoID,
						    [GameTypeID] = @GameTypeID,[GameKindID] = @GameKindID,[GameNameID] = @GameNameID,
						    [EnableRoom] = @EnableRoom,[IDSort] = @IDSort,
						    [Version] = @Version,[ServiceName] = @ServiceName,
						    [BattleRoomID]=@BattleRoomID,[BattleMatchTable]=@BattleMatchTable,[RoomPassword]=@RoomPassword ,[SendTimeLength]=@SendTimeLength,[SendCount]=@SendCount 
						    WHERE id=@RoomID;

						    UPDATE [TGameRoomBase] SET 
						    [RoomRule] = @RoomRule,[DeskCount] = @DeskCount,[MaxPeople] = @MaxPeople,
						    [BasePoint] = @BasePoint,[LessPoint] = @LessPoint,[Tax] = @Tax,
						    [RunPublish] = @RunPublish,[PlayTimes]=@PlayTimes,[PlayTimesMoney]=@PlayTimesMoney,[PlayCounts_1]=@PlayCounts_1,
                            [PlayCountsMoney_1]=@PlayCountsMoney_1,[PlayCounts_2]=@PlayCounts_2,[PlayCountsMoney_2]=@PlayCountsMoney_2,
                            [PlayCounts_3]=@PlayCounts_3,  [PlayCountsMoney_3]=@PlayCountsMoney_3,[MaxPoint]=@MaxPoint,[ExercisePoint]=@ExercisePoint,ContestID=@ContestID
						    WHERE RoomID=@RoomID ;

						    UPDATE [TGameRoomMsg] SET 
						    [RoomWelcome] = @RoomWelcome,[RallWelcome] = @RallWelcome
						    WHERE RoomID=@RoomID ;

						    UPDATE [TGameRoomTable] SET 
						    [TableLock] = @TableLock,[TableIPRule] = @TableIPRule,[TableMatch] = @TableMatch,
						    [TableUserNameRule] = @TableUserNameRule
						    WHERE RoomID=@RoomID 
                        end
						";

        DbSession.Default.FromSql(sql)
            .AddInputParameter("@RoomID", DbType.String, RoomsId)
            .AddInputParameter("@RoomName", DbType.String, sqlRoomName)
            .AddInputParameter("@ServerIP", DbType.String, sqlServiceIP)
            .AddInputParameter("@ServerInfoID", DbType.String, sqlServerInfoID)
            .AddInputParameter("@GameTypeID", DbType.String, sqlComType)
            .AddInputParameter("@GameKindID", DbType.String, sqlkindid)
            .AddInputParameter("@GameNameID", DbType.String, sqlComName)
            .AddInputParameter("@EnableRoom", DbType.String, sqlbEnableRoom)
            .AddInputParameter("@IDSort", DbType.String, sqlIDSort)
            .AddInputParameter("@Version", DbType.String, sqlVersion)
            .AddInputParameter("@ServiceName", DbType.String, sqlServiceName)
            .AddInputParameter("@RoomRule", DbType.String, sqlRoomRule)
            .AddInputParameter("@DeskCount", DbType.String, sqlDeskCount)
            .AddInputParameter("@MaxPeople", DbType.String, sqlMaxPeople)
            .AddInputParameter("@BasePoint", DbType.String, sqlBasePoint)
            .AddInputParameter("@LessPoint", DbType.String, sqlLessPoint)
            .AddInputParameter("@Tax", DbType.String, sqltax)
            .AddInputParameter("@RunPublish", DbType.String, sqlRunPublish)
            .AddInputParameter("@RoomWelcome", DbType.String, sqlRoomWelcome)
            .AddInputParameter("@RallWelcome", DbType.String, sqlRallWelcome)
            .AddInputParameter("@TableLock", DbType.String, sqlLockTable)
            .AddInputParameter("@TableIPRule", DbType.String, sqlIPRuleTable)
            .AddInputParameter("@TableMatch", DbType.String, sqlMatchTable)
            .AddInputParameter("@BattleRoomID", DbType.String, battleRoomID)
            .AddInputParameter("@BattleMatchTable", DbType.String, battleMatchTable)
            .AddInputParameter("@TableUserNameRule", DbType.String, sqlUserNameRuleTable)
            .AddInputParameter("@RoomPassword", DbType.String, sqlRoomPassword)
            .AddInputParameter("@PlayTimes", DbType.String, (Convert.ToInt32(sqlPlayTimes) * 60).ToString())
            .AddInputParameter("@PlayTimesMoney", DbType.String, sqlPlayTimesMoney)
            .AddInputParameter("@PlayCounts_1", DbType.String, sqlPlayCounts_1)
            .AddInputParameter("@PlayCountsMoney_1", DbType.String, sqlPlayCountsMoney_1)
            .AddInputParameter("@PlayCounts_2", DbType.String, sqlPlayCounts_2)
            .AddInputParameter("@PlayCountsMoney_2", DbType.String, sqlPlayCountsMoney_2)
            .AddInputParameter("@PlayCounts_3", DbType.String, sqlPlayCounts_3)
            .AddInputParameter("@PlayCountsMoney_3", DbType.String, sqlPlayCountsMoney_3)
            .AddInputParameter("@MaxPoint", DbType.String, sqlMaxPoint)
             .AddInputParameter("@ExercisePoint", DbType.Int64, sqlExercisePoint)
             .AddInputParameter("@ContestID", DbType.Int32, sqlContestID)
             .AddInputParameter("@SendTimeLength", DbType.Int32, sqlSendTimeLength)
             .AddInputParameter("@SendCount", DbType.Int64, sqlSendCount)
            .Execute();

        Alert("操作成功！", "GameRooms.aspx");
    }

}
