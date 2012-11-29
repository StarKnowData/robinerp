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

public partial class Admin_Games_GameRoomsAdd : AdminBasePage
{
    public string LoginIp;
    string sqlServerInfoID, Sid;
    string sortid;
    //string socketprot;
    protected string TaxType;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");
        TaxType = UiCommon.StringConfig.RoomTaxSelected;
        if (string.IsNullOrEmpty(TaxType) || !CommonManager.String.IsInteger(TaxType))
            TaxType = "1";
        LoginIp = CommonManager.Web.GetIP();
        sortid = CommonManager.Web.Request("sortid", "");
        //Response.Write(sortid);
        //判断参数是否为空(注意:空有两种形式,一种为null,一种为空)
        if (!string.IsNullOrEmpty(sortid))
        {
            //如果有传递上述参数,则表示联动操作开始
            this.xmlBind(sortid);
        }

        //在页面初次加载的时候,绑定第一/二个下拉框,第二个下拉框为所有值
        //但实际上,第二个下拉框应显示空值,因为所有值可能也不少,最好只显示一个"请选择"字样
         if (!IsPostBack)
        {
            this.DownBind1();
            this.DownBind2();
        }
    }

    #region 二级联动
    /// <summary>
    /// 返回第2个下拉框需要的值给xmlhttp
    /// </summary>
    /// <param name="sortid">传递的关键ID值</param>
    private void xmlBind(string sortid)
    {
        string mystr = "";
        DataTable sd = new DataTable();
        string sql = "select * from TGameNameInfo Where Kindid=" + sortid + "";
        // Response.Write(sql);
        //DataTable mytab = this.Get_Dt(sql);
        sd = DbSession.Default.FromSql(sql).ToDataTable(); // sqlconn.sqlReader(sql);
        //将取到的值形成: ID|名称,ID|名称...这样的形式
        if (sd.Rows.Count > 0)
        {
            for (int i = 0; i < sd.Rows.Count; i++)
            {
                mystr += "," + sd.Rows[i]["Nameid"].ToString() + "|" + sd.Rows[i]["ComName"].ToString();
                //NameIDS += "," + sd.Rows[i]["Nameid"].ToString() + "|" + sd.Rows[i]["ComName"].ToString();
            }
            mystr = mystr.Substring(1);
        }

        //输出页面
        this.Response.Write(mystr);
        this.Response.End();
    }

    /// <summary>
    /// 绑定第一个下拉框
    /// </summary>
    private void DownBind1()
    {
        //显示所有的主分类
        DataTable sd2 = new DataTable();
        string sql = "select * from TGameKindInfo order by IDSort DESC ";
        // DataTable mytab = this.Get_Dt(sql);
        sd2 = DbSession.Default.FromSql(sql).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd2.Rows.Count > 0)
        {
            //绑定第一个下拉框
            this.kindid.DataSource = sd2;
            this.kindid.DataValueField = "Kindid";
            this.kindid.DataTextField = "KindName";
            this.kindid.DataBind();

            //添加一个"请选择"行
            this.kindid.Items.Insert(0, new ListItem("请选择类别", ""));

            //为此下拉框添加一个默认选择项(此处默认为sortid = 1
            //做选项时,如果您添加的选定项而此控件中却没有此项,即会出错
            //如:this.mydown1.SelectedValue = "1";
            //所以此处以如下方式进行选定			
            ListItem myItem = this.kindid.Items.FindByValue("1");
            //Response.Write(myItem);
            //Response.End();
        }
        // if (myItem != null)
        // {
        //      myItem.Selected = true;
        // }

        //为此下拉框添加选择事件,第一个参数是自己,第二个参数为要填充的下拉框的名称 
        this.kindid.Attributes.Add("onchange", "XmlPost(this,'" + this.NameID.ClientID + "');");
        //Response.Write(""+this.NameID.ClientID+"");
    }

    /// <summary>
    /// 绑定第二个下拉框
    /// </summary>
    private void DownBind2()
    {
        // 默认显示分类号为1的所有子类
        DataTable sd3 = new DataTable();
        string sql = "select * from TGameNameInfo";
        sd3 = DbSession.Default.FromSql(sql).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd3.Rows.Count > 0)
        {

            //绑牢控件
            this.NameID.DataSource = sd3;
            this.NameID.DataSource = sd3;
            this.NameID.DataValueField = "Nameid";
            this.NameID.DataTextField = "ComName";
            this.NameID.DataBind();
            //添加一个空的首行
            this.NameID.Items.Insert(0, new ListItem("请选择名称", ""));
        }
    }
    #endregion


    #region 数据处理
    protected void AddRoomGame(object sender, EventArgs e)
    {
        string sqlComType, sqlkindid, sqlNameID, sqlRoomName, sqlServiceIP, sqlDeskCount, sqlMaxPeople, sqltax, sqlBasePoint, sqlLessPoint, sqlMaxPoint, sqlExercisePoint, sqlContestID;
        string sqlRoomRule, sqlIDSort, sqlbEnableRoom, sqlServiceName, sqlVersion, sqlRoomWelcome, sqlRallWelcome, sqlRunPublish, sqlMatchTable;
        string sqlNameIDs, sqlTaxType, sqlRoomPassword;//伯乐棋牌中增加密码房间;
        string sqlPlayTimes, sqlPlayTimesMoney, sqlPlayCounts_1, sqlPlayCountsMoney_1, sqlPlayCounts_2, sqlPlayCountsMoney_2, sqlPlayCounts_3, sqlPlayCountsMoney_3;
        int roomCounts;
        string sqlSendTimeLength, sqlSendCount;
        roomCounts =Convert.ToInt32( CommonManager.Web.RequestForm("txtRoomCounts", "1"));

        sqlComType = CommonManager.Web.RequestForm("ComType", "");//Limit.editCharacter( Limit.getFormValue( "ComType" ) ).ToString();
        sqlkindid = this.kindid.Text.ToString();
        if (sqlkindid.ToString() == "")
        {
            Alert("温馨提示：\\n\\n游戏类别不能为空！", null);
            return;
        }
        sqlNameID = this.NameID.Text.ToString();
        sqlNameIDs = CommonManager.Web.RequestForm("NameIDs", "");//Limit.editCharacter( Limit.getFormValue( "NameIDs" ) ).ToString();

        //Response.Write(sqlkindid + "<br>");
        //if (sqlNameID.ToString() == "")
        //    Response.Write(sqlNameIDs);
        //else
        //    Response.Write(sqlNameID + "<br>");
        //Response.End();
        sqlMaxPoint = CommonManager.Web.RequestForm("MaxPoint", "0");

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
        //    sqlTaxType = CommonManager.Web.RequestForm("raTaxType", "");

        //if (sqlTaxType == "0")//如果选中的门票就不要判断税率的值，并将税率给默认值0   周圣华 2010-08-26
        //{
        //    sqlTicket = CommonManager.Web.RequestForm("Ticket", "");
        //    if (!CommonManager.String.IsInteger(sqlTicket))
        //    {
        //        CommonManager.Web.RegJs(this, "alert('[" + UiCommon.StringConfig.RoomTaxName + "]必须为数字！');location.href=location.href;", false);
        //        return;
        //    }

        //    sqltax = "0";
        //}
        //else//如果选中的税率就不要判断门票的值，并将门票给默认值0
        //{
        //    sqltax = CommonManager.Web.RequestForm("TaxPercent", "");//Limit.editCharacter( Limit.getFormValue( "tax" ) ).ToString();
        //    if (!CommonManager.String.IsInteger(sqltax))
        //    {
        //        CommonManager.Web.RegJs(this, "alert('[税率]必须为数字！');location.href=location.href;", false);
        //        return;
        //    }
        //    sqlTicket = "0";
        //}
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

        sqlRoomRule = CommonManager.Web.RequestForm("RoomRule", "");
        if (string.IsNullOrEmpty(sqlRoomRule))
        {
            CommonManager.Web.RegJs(this, "alert('[游戏规则]不能为空！');location.href=location.href;", false);
            return;
        }
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
        if (!CommonManager.String.IsInteger(sqlIDSort))
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

        string battleMatchTable = CommonManager.Web.RequestForm("txtBattleMatchTable", "");// Limit.editCharacter( Limit.getFormValue( "txtBattleMatchTable" ) );
        if (CommonManager.String.IsInteger(battleRoomID) && (int.Parse(battleRoomID) > 0))
        {
            string sqlbtr = "select * from [TBattleRoomInfo] where BattleRoomID=" + battleRoomID;
            DataTable tmpBTR = DbSession.Default.FromSql(sqlbtr).ToDataTable(); //sqlconn.sqlReader( sqlbtr );
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
            battleRoomID = "0";
            battleMatchTable = "TBattleMatchTable";
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
        sqlRoomPassword =(CommonManager.Web.RequestForm("RoomPassword","")=="")?"": CommonManager.String.EncryptMD5SystemDefaultMethod(CommonManager.Web.RequestForm("RoomPassword", ""), false, true);//伯乐棋牌中增加密码房间
        if (!Utility.Common.IsPositiveNumber(sqlRunPublish))
        {
            CommonManager.Web.RegJs(this, "alert('[逃跑]必须为非负数！');location.href=location.href;", false);
            return;
        }
        DataTable sd4 = new DataTable();
        string sql4 = "select top 1 ComProcess from TGameNameInfo where NameID=" + sqlNameID + "";
        sd4 = DbSession.Default.FromSql(sql4).ToDataTable();//sqlconn.sqlReader( sql4 );
        if (sd4.Rows.Count > 0)
        {
            sqlMatchTable = "TMatchTable";
        }
        else
        {
            Alert("温馨提示：\\n\\n查询游戏名称信息时出错，请检测游戏名称！", null);
            return;
        }

        DataTable sd3 = new DataTable();
        string sql3 = "select ServerInfoID from TGameServerInfo where NameID=" + sqlNameID + "";
        //Response.Write(sql3);
        //Response.End();
        sd3 = DbSession.Default.FromSql(sql3).ToDataTable();
        if (sd3.Rows.Count > 0)
        {
            sqlServerInfoID = sd3.Rows[0]["ServerInfoID"].ToString();
        }
        else
        {
            Alert("温馨提示：\\n\\n查询游戏服务端ID号时失败！", null);
            return;
        }


        //DataTable sdt = new DataTable();
        //string sqlt = "select max(socketport) as socketprot from TGameRoomInfo";
        //sdt = DbSession.Default.FromSql(sqlt).ToDataTable();//sqlconn.sqlReader( sqlt );
        //if (sdt.Rows.Count > 0)
        //{
        //    socketprot = sdt.Rows[0]["socketprot"].ToString();
        //    if (socketprot.ToString() == "")
        //        socketprot = "0";
        //}
        //sdt.Clear();

        //Response.Write(socketprot);
        //Response.End();
        //增加在线时长送金币，局数送金币
        sqlPlayTimes = CommonManager.Web.RequestForm("txtPlayTimes", "");
        sqlPlayTimesMoney = CommonManager.Web.RequestForm("txtPlayTimesMoney", "");
        if (!CommonManager.String.IsInteger(sqlPlayTimes) || !CommonManager.String.IsInteger(sqlPlayTimesMoney) || Convert.ToInt64(sqlPlayTimesMoney)<0 || Convert.ToInt32(sqlPlayTimes)<0)
        {
            Alert("温馨提示：\\n\\n在线时长和所送金币数必须为非负数！", null);
            return;
        }
        sqlPlayCounts_1 = CommonManager.Web.RequestForm("txtPlayCounts_1", "");
        sqlPlayCounts_2 = CommonManager.Web.RequestForm("txtPlayCounts_2", "");
        sqlPlayCounts_3 = CommonManager.Web.RequestForm("txtPlayCounts_3", "");
        if (!CommonManager.String.IsInteger(sqlPlayCounts_1) || !CommonManager.String.IsInteger(sqlPlayCounts_2) || !CommonManager.String.IsInteger(sqlPlayCounts_3))
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
       
        sqlExercisePoint = CommonManager.Web.RequestForm("ExercisePoint", "50000");
        if (!CommonManager.String.IsFloat(sqlExercisePoint))
        {
            Alert("温馨提示：\\n\\n练习房间进入默认金币必须为数字！", null);
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
        //比赛id
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
            sqlbtr = "select count(roomid) from TGameRoomBase where ContestID=" + sqlContestID;
            tmpBTR.Clear();
            tmpBTR = DbSession.Default.FromSql(sqlbtr).ToDataTable();// sqlconn.sqlReader( sqlbtr );
            if (tmpBTR.Rows.Count > 0 && ((int)tmpBTR.Rows[0][0] > 0))
            {
                CommonManager.Web.RegJs(this, "alert('您填写的比赛id已经被用在别的房间了，请重新输入！');location.href=location.href;", true);
                return;
            }

        }
        else
        {
            sqlContestID = "0";

        }
        string sql=string.Empty;
        for (int i = 0; i < roomCounts; i++)
        {
            try
            {
               // Sid = Utility.SqlHelper.GetMaxID("id", "TGameRoomInfo").ToString();
                sql = @"
                        Declare @RoomID int
                        select @RoomID =isnull(max(id),0)+1 from TGameRoomInfo
                        Declare @SocketPortOld int
                        select @SocketPortOld=isnull(Max(SocketPort),0)+1 from TGameRoomInfo
                        
						INSERT INTO TGameRoomInfo ([id],[RoomID],[RoomName],[ServerIP],[ServerInfoID],[GameTypeID],
						[GameKindID],[GameNameID],[SocketPort],[OnlineCount],[UpdateTime],[EnableRoom],[StopLogon],
						[IDSort],[Version],[ServiceName],[BattleRoomID],[BattleMatchTable],[RoomPassword],[SendTimeLength],[SendCount])
						VALUES (@RoomID,@RoomID,@RoomName,@ServerIP,@ServerInfoID,@GameTypeID,
						@GameKindID,@GameNameID,@SocketPortOld,@OnlineCount,getdate(),@EnableRoom,@StopLogon,
						@IDSort,@Version,@ServiceName,@BattleRoomID,@BattleMatchTable,@RoomPassword,@SendTimeLength,@SendCount);

						INSERT INTO TGameRoomBase ([RoomID],[RoomRule],[DeskCount],[MaxPeople],[BasePoint],
						[LessPoint],[MoneyPoint],[Tax],[UserPower],[MaxLimite],[RunPublish],[PlayTimes],[PlayTimesMoney],[PlayCounts_1],[PlayCountsMoney_1],[PlayCounts_2],[PlayCountsMoney_2],[PlayCounts_3],[PlayCountsMoney_3],[MaxPoint],[ExercisePoint],[ContestID])
								VALUES (@RoomID,@RoomRule,@DeskCount,@MaxPeople,@BasePoint,
						@LessPoint,@MoneyPoint,@Tax,@UserPower,@MaxLimite,@RunPublish,@PlayTimes,@PlayTimesMoney,@PlayCounts_1,
                        @PlayCountsMoney_1,@PlayCounts_2,@PlayCountsMoney_2,@PlayCountsMoney_2,@PlayCountsMoney_3,@MaxPoint,@ExercisePoint,@ContestID);

						INSERT INTO TGameRoomMsg ([RoomID],[RoomWelcome],[RallWelcome])
							VALUES (@RoomID,@RoomWelcome,@RallWelcome);

						INSERT INTO TGameRoomTable ([RoomID],[TableLock],[TableIPRule],[TableMatch],[TableUserNameRule])
							VALUES (@RoomID,'TGameLock','TRoomIPRule','Tmatchtable','TUserNameRule');
						";

                DbSession.Default.FromSql(sql)
                   .AddInputParameter("@RoomName", DbType.String, sqlRoomName)
                    .AddInputParameter("@ServerIP", DbType.String, sqlServiceIP)
                    .AddInputParameter("@ServerInfoID", DbType.String, sqlServerInfoID)
                    .AddInputParameter("@GameTypeID", DbType.String, sqlComType)
                    .AddInputParameter("@GameKindID", DbType.String, sqlkindid)
                    .AddInputParameter("@GameNameID", DbType.String, string.IsNullOrEmpty(sqlNameID) ? sqlNameIDs : sqlNameID)
                    .AddInputParameter("@OnlineCount", DbType.String, "0")
                    .AddInputParameter("@EnableRoom", DbType.String, sqlbEnableRoom)
                    .AddInputParameter("@StopLogon", DbType.String, "0")
                    .AddInputParameter("@IDSort", DbType.String, sqlIDSort)
                    .AddInputParameter("@Version", DbType.String, sqlVersion)
                    .AddInputParameter("@ServiceName", DbType.String, sqlServiceName)
                    .AddInputParameter("@RoomRule", DbType.String, sqlRoomRule)
                    .AddInputParameter("@DeskCount", DbType.String, sqlDeskCount)
                    .AddInputParameter("@MaxPeople", DbType.String, sqlMaxPeople)
                    .AddInputParameter("@BasePoint", DbType.String, sqlBasePoint)
                    .AddInputParameter("@LessPoint", DbType.String, sqlLessPoint)
                    .AddInputParameter("@MoneyPoint", DbType.String, "0")
                    .AddInputParameter("@Tax", DbType.String, sqltax)
                    .AddInputParameter("@UserPower", DbType.String, "0")
                    .AddInputParameter("@MaxLimite", DbType.String, "0")
                    .AddInputParameter("@RunPublish", DbType.String, sqlRunPublish)
                    .AddInputParameter("@RoomWelcome", DbType.String, sqlRoomWelcome)
                    .AddInputParameter("@RallWelcome", DbType.String, sqlRallWelcome)
                    .AddInputParameter("@BattleRoomID", DbType.String, battleRoomID)
                    .AddInputParameter("@BattleMatchTable", DbType.String, battleMatchTable)
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
                     .AddInputParameter("@ContestID", DbType.String, sqlContestID)
                     .AddInputParameter("@SendTimeLength", DbType.Int32, sqlSendTimeLength)
                     .AddInputParameter("@SendCount", DbType.Int64, sqlSendCount)
                    .Execute();
            }
            catch (Exception ex)
            {
                Response.Write(ex.Message + sql);
                Response.End();
            }
        }
        Alert("操作成功！", "GameRooms.aspx");

    }

    #endregion

}
