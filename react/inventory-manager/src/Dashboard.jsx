import { createElement, useState } from 'react'
import './dashboard.css'

function Item({name, count, onRemoveItem, onRenameItem, onChangeCount}) {
  const [isEditting, setIsEditting] = useState(true);
  const [localName, setLocalName] = useState(name);
  const [localCount, setLocalCount] = useState(count);

  const toggleisEditting = () => {
    setIsEditting(!isEditting)
    setLocalName(name);
  }

  const pressKey = (event) => {
    if (event.key == "Enter") {
      confirmTextChange()
    }
  }

  const confirmTextChange = () => {
    onRenameItem(localName)
    setIsEditting(false);
  }

  const incrementCount = () => {
    setLocalCount(localCount + 1);
    onChangeCount(localCount + 1);
  }

  const decrementCount = () => {
    if (count == 1) {
      onRemoveItem();
    } else {
      setLocalCount(localCount - 1);
      onChangeCount(localCount - 1);
    }
  }

  const TextShower = () => {
    if (isEditting) {
      return (
        <input type="text" 
          placeholder={name} 
          className='ItemEdit' 
          onChange={(e) => setLocalName(e.target.value)}
          onBlur={confirmTextChange}
          onKeyDown={pressKey}
          autoFocus
        />
      )
    }
    return (
      name + ": " + count
    )
  }

  return (
    <>
      <div className='row'>
        {TextShower()}

        <div>
          <button onClick={toggleisEditting}>
            ?
          </button>

          <button onClick={incrementCount}>
            +
          </button>

          <button onClick={decrementCount}>
            -
          </button>


          <button onClick={onRemoveItem}>
            rm
          </button>
          </div>
      </div>
    </>
  )
}

function ItemAdder({onAddNewItem}) {

  return (
    <>
      <button onClick={onAddNewItem}>
        +
      </button>
    </>
  )
}


function Dashboard() {
  const [items, setItems] = useState([]);

  const onAddNewItem = () => {
    const newItems = items.slice();
    newItems.push({name: "Item", count: 1});
    setItems(newItems);
  }

  const onRemoveItem = ({index}) => {
    const newItems = items.slice();
    newItems.splice(index, 1);
    setItems(newItems);
  }

  const onRenameItem = (index, new_name) => {
    let newItems = items.slice();
    newItems[index].name = new_name;
    setItems(newItems);
  }

  const onChangeCount = (index, new_count) => {
    let newItems = items.slice();
    newItems[index].count = new_count;
    setItems(newItems);
  }

  return (
    <>
      <div className='DashBoard'>
        Stock
        <div className='ItemList' id="ItemList">
          {items.map((item, index) => (
            <Item key={index} 
              name={item.name} 
              count={item.count} 
              onRemoveItem={() => onRemoveItem(index)}
              onRenameItem={(new_name) => onRenameItem(index, new_name)}
              onChangeCount={(new_count) => onChangeCount(index, new_count)}
            />
          ))}
          <ItemAdder onAddNewItem={onAddNewItem}/>
        </div>
      </div>
    </>
  )
}

export default Dashboard
