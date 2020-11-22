<template>
  <div class="star-container">
    <ul>
      <!-- 
                num 2.3 1 2 3亮
                        4 5不亮
                    2   1 2 亮
                        3 4 5 不亮

             -->
      <li
        v-for="i in 5"
        :key="i"
        :class="{
          active: i <= num,
          'half-active': i - num > 0 && i - num < 1,
          unactive: i > Math.ceil(num),
        }"
      ></li>
      <!-- <li class="active"></li>
            <li class="half-active"></li>
            <li class="unactive"></li> -->
    </ul>
  </div>
</template>

<script>
export default {
  props: {
    num: {
      type: Number,
      default: 5,
    },
  },
};
</script>

<style lang="scss" scoped>
.star-container {
    display: inline-block;
    vertical-align: center;
  ul {
    float: left;
    display: flex;
    li {
      width: 12px;
      height: 12px;
      margin-right: 2px;
      background-size: 12px;
    }
  }
  .active {
    background-image: url("./images/star-active.png");
  }
  .unactive {
    background-image: url("./images/star.png");
  }
  .half-active {
    background-image: url("./images/star-half.png");
  }
}
</style>