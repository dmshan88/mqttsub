<?php
namespace app\models;

use Yii;
// use yii\db\Query;
use yii\db\Command;
// use app\models\cpdb\ErrCode;
use app\models\Machine;
use app\models\Newstat;
use app\models\Historystat;


class Routine
{
    
    private $errCode = 0;
    private $errMsg = '';
    const CMD_INIT = 1;
    const CMD_CONNECTED = 2;
    const CMD_DISCONNECT = 3;

    
    private function log($value='', $level = 'info')
    {
        $value = is_string($value) ? $value : '(bad input)' ;
        switch ($level) {
            
            case 'trace':
                Yii::debug($value, 'routine');
                break;
             case 'waring':
                Yii::warning($value, 'routine');
                break; 
            case 'error':
                Yii::error($value, 'routine');
                break;          
            default:
                Yii::info($value, 'routine');
                break;
        }
    }

    public function test()
    {
        Yii::$app->db->createCommand()->truncateTable('newstat')->execute();
    }

    public function parseCmd($cmd = '', $mid = '', $clientid = '')
    {
        $tmpstr = '';
        switch ($cmd) {
            case self::CMD_INIT :
                $tmpstr = sprintf("%s init", $clientid);
                $this->log($tmpstr);
                $this->resetNewstat();
                break;

            case self::CMD_CONNECTED :
                $ret = $this->addNewstat($mid, $cmd);
                break;

            case self::CMD_DISCONNECT :
                $ret = $this->addNewstat($mid, $cmd);
                break;

            default:
                $tmpstr = sprintf("%s bad cmd", $cmd);
                $this->log($tmpstr);
                return false;
                break;
        }
        return $ret;
    }

    public function resetNewstat($mid = '')
    {
        Yii::$app->db->createCommand()->truncateTable('newstat')->execute();
    }

    public function addNewstat($mid = '', $cmd = '')
    {
        if (! strpos($mid, 'unset') === false) {
            return ;
        }
        $machineid = substr($mid, -6);
        $Machine = Machine::findOne($machineid);
        $Historystat = new Historystat();
        $transaction = $Historystat->getDb()->beginTransaction();
        try {
            if (!$Machine) {      
                $Machine = new Machine();          
                $Machine->setAttributes([
                    'id' => $machineid,
                    'clientid' => $mid,
                    'mtype' => substr($mid, 0, -7),
                ]);
                if (!$Machine->save()) {
                    throw new \Exception('Machine add fail', 1);
                }
                $this->log("add machine success");
            }
            $data = [
                'machine_id' => $Machine->id,
                'online' => ($cmd == self::CMD_CONNECTED) ? 'Y' : 'N' ,
                'activetime' => date('Y-m-d H:i:s'),
            ];
            $Newstat = $Machine->newstat;
            if (empty($Newstat)) {
                $Newstat = new Newstat();
                $Newstat->machine_id = $data['machine_id'];
            }
            if ($Newstat->online == $data['online']) {
                $this->log("stat same?");
            }
            $Newstat->online = $data['online'];
            $Newstat->activetime = $data['activetime'];
            if (!$Newstat->save()) {
                throw new \Exception('Newstat add fail', 1);
            }

            $Historystat->setAttributes($data);
            if (!$Historystat->save()) {
                throw new \Exception('Historystat add fail', 1);
            }
            $transaction->commit();
            $this->log(sprintf("%s online : %s", $data['machine_id'], $data['online']));
            return true;

        } catch (\Exception $e) {
            $this->errCode = "DATABASE_ERR";
            $this->errMsg = $e->getMessage();
            $transaction->rollBack();
            $this->log($this->errMsg, 'error');
            return false;
        } catch (\Throwable $e) {
            $this->errCode = "DATABASE_ERR";
            $this->errMsg = $e->getMessage();
            $this->log($this->errMsg, 'error');
            $transaction->rollBack();
            return false;
        }
    }

    public function getErrCode()
    {
        return $this->errCode;
    }

    public function getErrMsg()
    {
        return $this->errMsg;
    }

}