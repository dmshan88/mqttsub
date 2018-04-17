<?php

namespace app\models;

use Yii;
use yii\base\Model;
use yii\data\ActiveDataProvider;
use app\models\Machine;

/**
 * MachineSearch represents the model behind the search form of `app\models\Machine`.
 */
class MachineSearch extends Machine
{
    public function attributes()
    {
        // add related fields to searchable attributes
        return array_merge(parent::attributes(), ['newstat.online','newstat.activetime', 'newpos.address']);
    }
    /**
     * @inheritdoc
     */
    public function rules()
    {
        return [
            [['id', 'clientid', 'mtype','newstat.online'], 'safe'],
        ];
    }

    /**
     * @inheritdoc
     */
    public function scenarios()
    {
        // bypass scenarios() implementation in the parent class
        return Model::scenarios();
    }

    /**
     * Creates data provider instance with search query applied
     *
     * @param array $params
     *
     * @return ActiveDataProvider
     */
    public function search($params)
    {
        $query = Machine::find();

        // add conditions that should always apply here

        $dataProvider = new ActiveDataProvider([
            'query' => $query,
        ]);

        $this->load($params);

        if (!$this->validate()) {
            // uncomment the following line if you do not want to return any records when validation fails
            // $query->where('0=1');
            return $dataProvider;
        }
        $query->joinWith(['newstat' => function($query) { $query->from(['newstat' => 'newstat']); }]);
        $query->joinWith(['newpos' => function($query) { $query->from(['newpos' => 'newpos']); }]);
        $dataProvider->sort->attributes['newstat.activetime'] = [
            'asc' => ['newstat.activetime' => SORT_ASC],
            'desc' => ['newstat.activetime' => SORT_DESC],
        ];
        // $dataProvider->sort->attributes['newstat.online'] = [
        //     'asc' => ['newstat.online' => SORT_ASC],
        //     'desc' => ['newstat.online' => SORT_DESC],
        // ];

        // grid filtering conditions
        $query->andFilterWhere(['like', 'id', $this->id])
            ->andFilterWhere(['like', 'clientid', $this->clientid])
            ->andFilterWhere(['like', 'mtype', $this->mtype]);
        $query->andFilterWhere(['LIKE', 'newstat.online', $this->getAttribute('newstat.online')]);

        $query->addOrderBy(['newstat.activetime' => SORT_DESC]);

        return $dataProvider;
    }
}
