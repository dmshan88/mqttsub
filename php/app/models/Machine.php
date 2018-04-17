<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "machine".
 *
 * @property string $id
 * @property string $clientid
 * @property string $mtype
 *
 * @property Historypos[] $historypos
 * @property Historystat[] $historystats
 * @property Newpos $newpos
 * @property Newstat $newstat
 */
class Machine extends \yii\db\ActiveRecord
{
    /**
     * @inheritdoc
     */
    public static function tableName()
    {
        return 'machine';
    }

    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['id'], 'required'],
            [['id'], 'string', 'max' => 10],
            [['clientid'], 'string', 'max' => 20],
            [['mtype'], 'string', 'max' => 14],
            [['id'], 'unique'],
        ];
    }

    /**
     * @inheritdoc
     */
    public function attributeLabels()
    {
        return [
            'id' => 'ID',
            'clientid' => 'Clientid',
            'mtype' => 'Mtype',
        ];
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getHistorypos()
    {
        return $this->hasMany(Historypos::className(), ['machine_id' => 'id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getHistorystats()
    {
        return $this->hasMany(Historystat::className(), ['machine_id' => 'id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getNewpos()
    {
        return $this->hasOne(Newpos::className(), ['machine_id' => 'id']);
    }

    /**
     * @return \yii\db\ActiveQuery
     */
    public function getNewstat()
    {
        return $this->hasOne(Newstat::className(), ['machine_id' => 'id']);
    }
}
