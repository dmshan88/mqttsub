<?php

namespace app\models;

use Yii;

/**
 * This is the model class for table "machine".
 *
 * @property string $id
 * @property string $clientid
 *
 * @property Historystat[] $historystats
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
        ];
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
    public function getNewstat()
    {
        return $this->hasOne(Newstat::className(), ['machine_id' => 'id']);
    }
}
